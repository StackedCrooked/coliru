#include <iostream>
#include <string>
#include <vector>

namespace xyz {
    
    class string: public std::string {
        
        string string(const string& s) {
            std::cout << "copy" << std::endl;
            return this;
        }
    };
    
}

using xyz::string:

class Exception {
    
public:    
    string message;
    
    Exception(string message) {
        this-> message = message;
    }
};

void f1() {
  throw Exception(string("bad"));   
}


int main()
{
    try {
        f1();
    }
    catch(Exception& e) {
        std::cerr << e.message << std::endl;
    }
    
    std::cout << "terminated!" << std::endl;
}


