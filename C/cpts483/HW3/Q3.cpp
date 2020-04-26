// Write an LLVM pass to measure the time spend in each function. The
// measurement should start before the first statement is executed and should
// end before the return statement.

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
  virtual bool runOnModule(Module &M);                // iters runOnFunction
  virtual bool runOnFunction(Function &F, Module &M); // iters runOnBasicBlock
};
} // namespace

//////// runOnModule: runs for each module, overrides class builtin
//
bool Pass483::runOnModule(Module &M) {
  bool modified = false;
  for (Function &F : M) { // for each function in module
    modified |= runOnFunction(F, M);
  }
  return modified;
}

//////// runOnFunction: runs for each functions, overrides class builtin
// called by runOnModule
bool Pass483::runOnFunction(Function &F, Module &M) {
  // track if if any modifications made

  // Build printf function handle
  std::vector<Type *> printfArgs;
  printfArgs.push_back(Type::getInt8PtrTy(
      M.getContext())); // specify the first argument, i8* is the return
                        // type of CreateGlobalStringPtr
  FunctionType *printfType =
      FunctionType::get(Type::getInt32Ty(M.getContext()), printfArgs,
                        true); // create function type with return type,
                               // argument types and if const argument
  FunctionCallee printF = M.getOrInsertFunction(
      "printf", printfType); // create function if not extern or defined

  // Build clock function handle
  std::vector<Type *> clockArgs;
  // clock returns a long and takes no args
  FunctionType *clockType =
      FunctionType::get(Type::getInt64Ty(M.getContext()), clockArgs, true);
  FunctionCallee clockF = M.getOrInsertFunction(
      "clock", clockType); // create function if not extern or defined

  // instruction builder
  IRBuilder<> Builder(M.getContext());
  llvm::CallInst *startTime;
  llvm::CallInst *endTime;
  bool modified = false;
  for (auto B = F.begin(); B != F.end(); B++) {
    if (B == F.begin()) { // first basic block

      // make insert point
      Instruction &I = *(*B).begin();
      Builder.SetInsertPoint(&I);

      // make format string
      Value *formatStr =
          Builder.CreateGlobalStringPtr(F.getName().str() + ": start \n");

      // print function name : start
      std::vector<Value *> argVec;
      argVec.push_back(formatStr);
      CallInst::Create(printF, argVec, "printf", &I);

      // start a clock
      std::vector<Value *> argVec2;
      startTime = CallInst::Create(clockF, argVec2, "clock", &I);
    }
    for (Instruction &I : *B) { // for each instruction in block
      if ((std::string)I.getOpcodeName() == "ret") { // if instruct is return

        // make insert point
        Builder.SetInsertPoint(&I);

        // get end time
        std::vector<Value *> argVec2;
        endTime = CallInst::Create(clockF, argVec2, "clock", &I);

        // get time spent
        BinaryOperator *timeSpent = BinaryOperator::Create(
            Instruction::Sub, endTime, startTime, "timeSpent", &I);

        // make format string
        Value *formatStr = Builder.CreateGlobalStringPtr(
            F.getName().str() + ": timespent %ld\n", "timeSpent");

        // print function name : start
        std::vector<Value *> argVec;
        argVec.push_back(formatStr);
        argVec.push_back(timeSpent);
        CallInst::Create(printF, argVec, "printf", &I);
      }
    }
  }
  return modified;
}

char Pass483::ID = 0;
static RegisterPass<Pass483> X("HW", "483 HW3 passes",
                               false /* Only looks at CFG */,
                               false /* Analysis Pass */);
