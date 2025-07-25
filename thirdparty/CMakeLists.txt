#
# LLVM/MLIR
#

# Macro to set LLVM build flags
macro(set_llvm_flags)
    # add type
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)

    set(LLVM_ENABLE_WARNINGS OFF CACHE BOOL "")
    set(LLVM_ENABLE_BINDINGS OFF CACHE BOOL "" FORCE)
    set(LLVM_ENABLE_RTTI ON CACHE BOOL "" FORCE)
    set(LLVM_ENABLE_EH ON CACHE BOOL "" FORCE)
    set(LLVM_ENABLE_BACKTRACES OFF CACHE BOOL "" FORCE)
    set(LLVM_ENABLE_CRASH_OVERRIDES OFF CACHE BOOL "" FORCE)
    set(LLVM_ENABLE_PROJECTS "mlir" CACHE STRING "" FORCE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR ENABLE_DEVELOPER_BUILD)
        set(LLVM_ENABLE_ASSERTIONS ON CACHE BOOL "" FORCE)
    else()
        set(LLVM_ENABLE_ASSERTIONS OFF CACHE BOOL "" FORCE)
    endif()
    set(LLVM_INCLUDE_TESTS OFF CACHE BOOL "" FORCE)
    set(LLVM_INCLUDE_BENCHMARKS OFF CACHE BOOL "" FORCE)
    set(LLVM_TARGETS_TO_BUILD "host" CACHE STRING "" FORCE)
    set(CROSS_TOOLCHAIN_FLAGS_ "" CACHE STRING "" FORCE)
    set(CROSS_TOOLCHAIN_FLAGS_NATIVE "" CACHE STRING "" FORCE)
    set(LLVM_ENABLE_TERMINFO OFF CACHE BOOL "" FORCE)
    # we do not use examples and having it enabled
    # makes cmake complains about long path on Windows
    set(LLVM_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(LLVM_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(LLVM_BUILD_UTILS ON CACHE BOOL "" FORCE)
    set(LLVM_INSTALL_UTILS ON CACHE BOOL "" FORCE)
endmacro()

# Set LLVM build flags
set_llvm_flags()

# Add the LLVM project directory
add_subdirectory(llvm-project/llvm EXCLUDE_FROM_ALL)

# Set MLIR source and binary directories
set(MLIR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/llvm-project/mlir/include")
set(MLIR_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/llvm-project/llvm/tools/mlir/include")
include_directories(SYSTEM ${MLIR_SOURCE_DIR} ${MLIR_BINARY_DIR})
