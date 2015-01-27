#include <memory>
int main() {    
    std::unique_ptr<int> p1 = 0;       // OK
    std::unique_ptr<int> p2 = new int; // error
}