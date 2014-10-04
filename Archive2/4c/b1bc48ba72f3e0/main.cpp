#include <llvm/IRBuilder.h>

int main() {
    llvm::IRBuilder<> builder(llvm::getGlobalContext());
    return 0;
}
