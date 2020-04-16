// Q2) Write an LLVM pass to print the function trace. The function trace of a
// program is the “list”(order matters) of the functions that were invoked
// during the program execution. For simplicity, assume that all functions are
// user-defined and the only exception is “printf”

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
  virtual bool runOnModule(Module &M); // when there is a Module
};
} // namespace

//////// runOnModule: runs for each module, overrides class builtin
//
bool Pass483::runOnModule(Module &M) {

  IRBuilder<> Builder(M.getContext());
  Function *mainFunc = M.getFunction("main");

  // only call from main
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

  for (auto bb = mainFunc->begin(); bb != mainFunc->end(); bb++) {
    for (auto it = bb->begin(); it != bb->end(); it++) {
      // insert at the end of main function
      if ((std::string)it->getOpcodeName() == "ret") {
        // insert printf at the end of main function, before return function
        Builder.SetInsertPoint(&*bb, it);
        auto &functionList = M.getFunctionList(); // gets the list of functions
        // add a printf to the end of every function which prints its name
        for (auto &function : functionList) {
          Value *formatStr =
              Builder.CreateGlobalStringPtr(function.getName().str() + "\n");
          std::vector<Value *> argVec;
          argVec.push_back(formatStr);
          CallInst::Create(printF, argVec, "printf", &*it);
        }
      }
    }
  }
  return true;
}

char Pass483::ID = 0;
static RegisterPass<Pass483> X("HW", "483 HW3 passes",
                               false /* Only looks at CFG */,
                               false /* Analysis Pass */);
