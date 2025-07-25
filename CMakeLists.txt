cmake_minimum_required(VERSION 3.24)

# Project settings
set(PROJECT_NAME TryFindPackages)
project(${PROJECT_NAME} 
    VERSION 1.0
    DESCRIPTION "LLVM/MLIR based project"
    LANGUAGES CXX)

# Add third-party dependencies
add_subdirectory(thirdparty EXCLUDE_FROM_ALL)

# Configure paths for LLVM and MLIR
set(LLVM_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/llvm-project)
list(APPEND CMAKE_PREFIX_PATH 
    ${PROJECT_BINARY_DIR}/thirdparty/llvm-project/llvm/lib/cmake/llvm
    ${PROJECT_BINARY_DIR}/thirdparty/llvm-project/llvm/tools/mlir/cmake/modules/CMakeFiles)

# Find and configure LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} at ${LLVM_DIR}")

# Find and configure MLIR
find_package(MLIR REQUIRED CONFIG)
message(STATUS "Found MLIR ${MLIR_PACKAGE_VERSION} at ${MLIR_DIR}")

# Configure CMake modules
list(APPEND CMAKE_MODULE_PATH 
    "${LLVM_CMAKE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/llvm-project/mlir/cmake/modules")

# Include required modules
include(TableGen)
include(AddLLVM)
include(AddMLIR)

set(LLVM_LINK_COMPONENTS Support TableGen)
file(GLOB_RECURSE SRC_FILES ./src/*.cpp)
add_llvm_executable(${PROJECT_NAME}
  ${SRC_FILES}
)
add_dependencies(${PROJECT_NAME} LLVMSupport LLVMTableGen)

# Configure TableGen
set(DIALECT_DIR ${PROJECT_SOURCE_DIR}/tablegen)
set(LLVM_TARGET_DEFINITIONS ${DIALECT_DIR}/dialect.td)
set(MLIR_TABLEGEN_EXE $<TARGET_FILE:mlir-tblgen>)
set(MLIR_TABLEGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/inc")
file(MAKE_DIRECTORY ${MLIR_TABLEGEN_OUTPUT_DIR})

# TableGen include paths
set(TABLEGEN_INCLUDES
    -I ${MLIR_INCLUDE_DIRS}
    -I ${LLVM_PROJECT_DIR}/mlir/include)

# Generate dialect files
mlir_tablegen("dialect.hpp.inc" -gen-dialect-decls -dialect=ELF ${TABLEGEN_INCLUDES})
mlir_tablegen("dialect.cpp.inc" -gen-dialect-defs -dialect=ELF ${TABLEGEN_INCLUDES})

# Configure LLVM libraries
llvm_map_components_to_libnames(LLVM_LIBS support core)

# Setup include directories using modern CMake target-based approach
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${DIALECT_DIR}
    ${MLIR_INCLUDE_DIRS}
    ${LLVM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${MLIR_TABLEGEN_OUTPUT_DIR}
    ${LLVM_PROJECT_DIR}/mlir/include
    ${LLVM_PROJECT_DIR}/llvm/include)

# Link libraries using modern CMake target-based approach
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LLVM_LIBS}
    MLIRDialect)

# Setup TableGen targets
add_public_tablegen_target(ProjectDialectIncGen)
add_custom_target(MLIRVPUXIncGenList)
add_dependencies(MLIRVPUXIncGenList ProjectDialectIncGen)
add_dependencies(${PROJECT_NAME} MLIRVPUXIncGenList)
