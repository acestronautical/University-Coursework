/*
 * dynamic_add_count.cpp
 * Copyright (C) 2020 Aravind SUKUMARAN RAJAM (asr) <aravind_sr@outlook.com>
 *
 * Distributed under terms of the GNU LGPL3 license.
 */

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
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/GlobalVariable.h"

#include <iostream>
using namespace llvm;

namespace {
struct Hello3 : public ModulePass {

  static char ID;
  Hello3() : ModulePass(ID) {}

  Constant *getConstUi64(int Val, LLVMContext &Context) {
    IntegerType *Ui64Type = IntegerType::getInt64Ty(Context);
    return ConstantInt::get(Ui64Type, Val);
  }

  CastInst *createConstGlobalString(const char *GlobString,
                                    LLVMContext &Context, Function &F) {
    Constant *PrintStringConstant =
        ConstantDataArray::getString(Context, GlobString);
    GlobalVariable *GPrintVal = new GlobalVariable(
        *F.getParent(), PrintStringConstant->getType(), true,
        GlobalValue::PrivateLinkage, PrintStringConstant, ".strprint");

    PointerType *I8PType = IntegerType::getInt8PtrTy(Context);
    Instruction *FirstInst = F.getEntryBlock().getFirstNonPHI();
    CastInst *CastToPtr =
        CastInst::CreatePointerCast(GPrintVal, I8PType, "tmp", FirstInst);
    return CastToPtr;
  }

  FunctionCallee getOrInsertMalloc(Module &M) {
    LLVMContext &Context = M.getContext();
    IntegerType *I64Type = IntegerType::getInt64Ty(Context);
    PointerType *I8PtrType = PointerType::getInt8PtrTy(Context);
    FunctionCallee Fmalloc = M.getOrInsertFunction(
        "malloc", FunctionType::get(I8PtrType, I64Type, false));
    return Fmalloc;
  }

  FunctionCallee getOrInsertMalloc483(Module &M) {
    LLVMContext &Context = M.getContext();
    IntegerType *I64Type = IntegerType::getInt64Ty(Context);
    PointerType *I8PtrType = PointerType::getInt8PtrTy(Context);
    ArrayRef<Type *> ArgType{I64Type, I8PtrType, I64Type};
    FunctionCallee Fmalloc = M.getOrInsertFunction(
        "malloc483", FunctionType::get(I8PtrType, ArgType, false));
    return Fmalloc;
  }

  bool runOnModule(Module &M) override {
    for (Function &F : M) {

      LLVMContext &Context = F.getContext();
      std::vector<CallInst *> RemList;

      for (BasicBlock &B : F) {
        for (Instruction &I : B) {
          /// dont use isa and cast --- directly use dyn_cast
          CallInst *Call = dyn_cast<llvm::CallInst>(&I);
          if (Call && Call->getCalledFunction()->getName() == "malloc") {
            RemList.push_back(Call);
          }
        }
      }

      /// lets fix all malloc calls()
      FunctionCallee Malloc483 = getOrInsertMalloc483(M);
      for (CallInst *I : RemList) {
        std::vector<Value *> Args;

        /// Malloc has only one argument ... but still this is the general code
        for (unsigned int i = 0; i < I->getNumArgOperands(); ++i) {
          Args.push_back(I->getArgOperand(i));
        }
        StringRef SrcFile = "-";
        unsigned int LineNo = 0;

        if (DILocation *Loc = I->getDebugLoc()) {
          LineNo = Loc->getLine();
          SrcFile = Loc->getFilename();
        }

        Args.push_back(createConstGlobalString(SrcFile.data(), I->getContext(),
                                               *I->getFunction()));
        Args.push_back(getConstUi64(LineNo, I->getContext()));
        CallInst *Tmp =
            CallInst::Create(Malloc483, ArrayRef<Value *>(Args), "call483", I);
        I->replaceAllUsesWith(Tmp);
        I->eraseFromParent();
      }
    }
    return true;
  }
};
} // namespace

char Hello3::ID = 0;
static RegisterPass<Hello3> X("malloc_interceptor", "3rd 483 pass",
                              false /* Only looks at CFG */,
                              false /* Analysis Pass */);
