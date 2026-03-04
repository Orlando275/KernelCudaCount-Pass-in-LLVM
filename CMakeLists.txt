cmake_minimum_required(VERSION 3.20)
project(KernelCudaCount LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(LLVM 23 REQUIRED CONFIG)
message(STATUS "LLVM version : ${LLVM_VERSION}")
message(STATUS "LLVM include : ${LLVM_INCLUDE_DIRS}")

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")
add_definitions(${LLVM_DEFINITIONS_LIST})


add_llvm_pass_plugin(KernelCudaCount
  src/KernelCudaCount.cpp
)


target_include_directories(KernelCudaCount
  PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(KernelCudaCount PROPERTIES PREFIX "")