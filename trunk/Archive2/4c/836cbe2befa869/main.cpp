#include <iostream>
#include <string>


using namespace std;

using std::string;

class hiall {
    string gethello();
    
    int main() {
        string words = gethello();
        
        std::cout << words << std::endl;
        
        return 0;
    }
    
    string gethello() {
        return "hello world";
    }
};