#ifndef LLVM_KERNELCUDACOUNT_H
#define LLVM_KERNELCUDACOUNT_H

#include "llvm/IR/PassManager.h"

namespace llvm
{

    class KernelCudaCountPass
        : public PassInfoMixin<KernelCudaCountPass>
    {
    public:
        PreservedAnalyses run(Function &F,
                              FunctionAnalysisManager &AM);
    };

} // namespace llvm

#endif