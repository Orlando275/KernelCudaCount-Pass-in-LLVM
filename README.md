# KernelCudaCount – LLVM Pass Plugin

KernelCudaCount is an LLVM pass plugin built with the New Pass Manager.
It analyzes LLVM IR and counts CUDA kernel launches and CUDA-operation calls.
The pass works at IR level and inspects function calls to detect CUDA operations.

---

## What I learned building this pass
Building this plugin required understanding:
- How the New Pass Manager works
- How to register a pass as a dynamic plugin
- How to iterate over IR instructions
- How to identify CallInst and extract callee names
- How LLVM is structured internally (headers, components, build system)
- How to build LLVM from source with plugin support enabled

### I also had to understand:

- The difference between Legacy Pass Manager and NPM (New Pass Manager)
- How opt loads external plugins
- How to configure CMake

---

## Tools I used

While navigating the LLVM source code:

- rg (ripgrep) – to search for classes and methods
- clangd – to explore definitions and references inside the LLVM codebase
- opt – to test and execute the pass

---

## Requirements

- LLVM built from source
- New Pass Manager enabled
### Example LLVM build configuration:
```bash
cmake -G Ninja ../llvm \
  -DLLVM_ENABLE_PROJECTS="clang" \
  -DLLVM_TARGETS_TO_BUILD="X86;NVPTX" \
  -DCMAKE_BUILD_TYPE=Release \
  -DLLVM_BUILD_LLVM_DYLIB=ON \
  -DLLVM_LINK_LLVM_DYLIB=ON \
  -DLLVM_ENABLE_RTTI=ON
```
## Building the plugin
```bash
mkdir build
cd build
cmake -DLLVM_DIR="/home/orlandoemanuelflorescastillo/Documentos/LLVM/llvm-project/build/lib/cmake/llvm"
make
```
## This generates:
```bash
KernelCudaCount.so
```

---

##Generating LLVM IR from CUDA
```bash
clang++ -x cuda --cuda-gpu-arch=sm_86 \
  --cuda-path=/usr/local/cuda \
  -emit-llvm -c test.cu -o test.bc
---
OR test.ll
```

## Running the pass
```bash
opt \
  -load-pass-plugin ./KernelCudaCount.so \
  -passes="kernelcudacount" \
  test.bc -disable-output
```
