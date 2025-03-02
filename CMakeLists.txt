
set(PROJECT_NAME TryFindPackages)
project(${PROJECT_NAME})

cmake_minimum_required(VERSION 3.24)

add_subdirectory(thirdparty EXCLUDE_FROM_ALL)

list(APPEND CMAKE_PREFIX_PATH ${PROJECT_BINARY_DIR}/thirdparty/llvm-project/llvm/lib/cmake/llvm)

find_package(LLVM REQUIRED CONFIG)
if(LLVM_FOUND)
  message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
  message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
endif()

# include(AddLLVM)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)
add_executable(${PROJECT_NAME}
  ${SRC_FILES}
)
add_dependencies(${PROJECT_NAME} LLVMSupport LLVMTableGen)
