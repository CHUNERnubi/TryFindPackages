
project(TryFindPackages)

cmake_minimum_required(VERSION 3.24)

find_package(LLVM REQUIRED CONFIG)
if(LLVM_FOUND)
  message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
  message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
endif()

# include(AddLLVM)

