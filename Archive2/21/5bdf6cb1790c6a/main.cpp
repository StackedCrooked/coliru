#include <iostream>

int main(int argc, char** argv) {
    try { throw 42; }
    catch (int e) { std::cout << e << "\n"; }
    
    return 0;
}