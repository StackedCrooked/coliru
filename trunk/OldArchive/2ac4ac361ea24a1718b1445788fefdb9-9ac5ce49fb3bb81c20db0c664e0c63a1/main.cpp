#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    std::vector<int> v(10);
    
    for (int i = v.size(); i--; ) {
    ///Stuff.
    std::cout << i << " " << std::flush;
    }
    std::cout << std::endl;
            
    for (int i = v.size() - 1; i>=0; i--) {
    ///Stuff.
    std::cout << i << " " << std::flush;
    }
    std::cout << std::endl;
        
}

