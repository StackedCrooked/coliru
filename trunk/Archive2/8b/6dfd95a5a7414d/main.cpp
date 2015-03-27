#include <iostream>
#include <string>


using namespace std;

using std::string;

class hiall {
    public:
    string gethello();
    
    string gethello() {
        return "hello world";
    }
};

int main() {
    hiall *hiclass = new hiall();
    string words = hiclass->gethello();
        
    std::cout << words << std::endl;
        
    return 0;
}