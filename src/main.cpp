#include <iostream>

// Include required MLIR headers
#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "llvm/Support/raw_ostream.h"

// Include generated files - they already contain the namespace declarations
#include "dialect.hpp.inc"
#include "dialect.cpp.inc"

int main () {
    std::cout << "hello world" << std::endl;
    return 0;
}
