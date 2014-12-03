#include <iostream>
#include <string>
#include <vector>

using namespace std;
    
class Exception {
    
public:    
    string message;
    
    Exception(string message) {
        this-> message = message;
    }
};


void f1() {
  throw Exception("bad");   
}

void f2() {
    f1();
}
    
int main()
{
    f2();
    
    std::cout << "terminated!" << std::endl;
}


