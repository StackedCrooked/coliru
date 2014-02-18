#include <vector>


int main() {
    auto buffer = new char[sizeof(std::vector<int>::iterator)];
    
    auto iterator = new((void*)buffer) std::vector<int>::iterator();
    iterator->std::vector<int>::iterator::~iterator();
    
    delete[] buffer;
}
