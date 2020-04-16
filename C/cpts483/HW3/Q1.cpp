// Q1) Count the total number of add instructions executed in a program
// print the o/p just before returning from main
// The count is not per function, we  are  not  counting  the  total  number  of
// add  instructions  a  program  (static),  the  total  number of add
// instructions that were executed during the program execution (dynamic).

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/GlobalVariable.h"

#include "llvm/IR/IRBuilder.h"

#include <iostream>
using namespace llvm;

namespace {
struct Pass483 : public ModulePass {

  static char ID;
  Pass483() : ModulePass(ID) {}
  virtual bool runOnModule(Module &M);                // when there is a Module
  virtual bool runOnFunction(Function &F, Module &M); // called by runOnModule
  virtual bool runOnBasicBlock(BasicBlock &B,
                               Module &M); // called by runOnFunction

  bool setup(Module &M);    // create global variables
  bool teardown(Module &M); // print stuff
};
} // namespace

//////// runOnModule: runs for each module, overrides class builtin
//
bool Pass483::runOnModule(Module &M) {
  // modified tracks whether something was modified
  bool modified = setup(M);
  for (Function &F : M) {
    // or equals to always be true if any are true
    modified |= runOnFunction(F, M);
  }
  modified |= teardown(M);
  return modified;
}

//////// runOnFunction: runs for each functions, overrides class builtin
// called by runOnModule
bool Pass483::runOnFunction(Function &F, Module &M) {
  // track if if any modifications made
  bool modified = false;

  if (F.isDeclaration()) {
    errs() << "Continue\n";
    return modified;
  }

  for (BasicBlock &B : F) {
    modified |= runOnBasicBlock(B, M);
  }
  return modified;
}

//////// runOnBasicBlock: runs for each basic block, overrides class builtin
// called by runOnFunction
bool Pass483::runOnBasicBlock(BasicBlock &B, Module &M) {
  // declare easier types
  Type *I64Ty = Type::getInt64Ty(M.getContext());

  Constant *instrCounter = M.getOrInsertGlobal("addCounter", I64Ty);

  for (Instruction &I : B) {                 // for each instruction in block
    if (I.getOpcode() == Instruction::Add) { // if add instruction
      // load counter value before current instruction
      LoadInst *LoadInstTmp = new LoadInst(I64Ty, instrCounter, "ctrload", &I);
      // add one to counter
      BinaryOperator *AddInstTmp =
          BinaryOperator::Create(Instruction::Add, ConstantInt::get(I64Ty, 1),
                                 LoadInstTmp, "counterinc", &I);
      // store value back to counter
      new StoreInst(AddInstTmp, instrCounter, &I);
    }
  }
  return true;
}

//////// setup: creates global values
// called by runOnModule
bool Pass483::setup(Module &M) {
  Function *mainFunc = M.getFunction("main");
  // not the main module
  if (!mainFunc)
    return false;

  // Create  counter global variable;
  Type *I64Ty = Type::getInt64Ty(M.getContext());
  new GlobalVariable(M, I64Ty, false, GlobalValue::CommonLinkage,
                     ConstantInt::get(I64Ty, 0), "addCounter");

  return true;
}

//////// teardown: prints results
// called at end of runOnModule
bool Pass483::teardown(Module &M) {

  IRBuilder<> Builder(M.getContext());
  Function *mainFunc = M.getFunction("main");

  // must be in main context
  if (!mainFunc)
    return false;

  // Build printf function handle
  std::vector<Type *> FTyArgs;
  FTyArgs.push_back(Type::getInt8PtrTy(
      M.getContext())); // specify the first argument, i8* is the return type of
                        // CreateGlobalStringPtr
  FunctionType *FTy =
      FunctionType::get(Type::getInt32Ty(M.getContext()), FTyArgs,
                        true); // create function type with return type,
                               // argument types and if const argument
  FunctionCallee printF = M.getOrInsertFunction(
      "printf", FTy); // create function if not extern or defined

  // assert(printF != NULL);

  for (auto bb = mainFunc->begin(); bb != mainFunc->end(); bb++) {
    for (auto it = bb->begin(); it != bb->end(); it++) {
      // insert at the end of main function
      if ((std::string)it->getOpcodeName() == "ret") {
        // insert printf at the end of main function, before return function
        Builder.SetInsertPoint(&*bb, it);

        // Build Arguments
        // create global string variable formatStr
        Value *formatStr = Builder.CreateGlobalStringPtr(
            "\n\n addCounter: %d\n", "addCounter");
        // printf will need a vector of args
        std::vector<Value *> argVec;
        argVec.push_back(formatStr);

        // get pointer pointing to the global variable name
        Value *addCounter = M.getGlobalVariable("addCounter");
        // addCounter only points to a string, but we want to print the number
        // the string stores
        Value *addValue =
            new LoadInst(addCounter, addCounter->getName() + ".val", &*it);
        argVec.push_back(addValue);
        // create printf function with the return value name called printf (with
        // suffix if already exists)
        CallInst::Create(printF, argVec, "printf", &*it);
      }
    }
  }
  return true;
}

char Pass483::ID = 0;
static RegisterPass<Pass483> X("HW", "483 HW3 passes",
                               false /* Only looks at CFG */,
                               false /* Analysis Pass */);
