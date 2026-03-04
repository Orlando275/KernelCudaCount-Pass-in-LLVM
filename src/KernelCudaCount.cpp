#include "KernelCudaCount.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"
using namespace llvm;

PreservedAnalyses KernelCudaCountPass::run(Function &F,
                                           FunctionAnalysisManager &AM)
{
    for (Instruction &I : instructions(F))
    {
        if (auto *CI = dyn_cast<CallBase>(&I))
            if (Function *Launch = CI->getCalledFunction())
            {
                StringRef Name = Launch->getName();

                if (Name.contains("cuda"))
                {
                    if (Name == "cudaLaunchKernel")
                    {

                        errs() << "Kernel Cuda was called : " << Launch->getName() << '\n';
                    }
                    else
                    {
                        errs() << "Cuda operation was called : " << Launch->getName()
                               << '\n';
                    }
                }
            }
    }
    return PreservedAnalyses::all();
}
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return {
        LLVM_PLUGIN_API_VERSION,
        "KernelCudaCount",
        "v0.1",
        [](PassBuilder &PB)
        {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>)
                {
                    if (Name == "kernelcudacount")
                    {
                        FPM.addPass(KernelCudaCountPass());
                        return true;
                    }
                    return false;
                });
        }};
}