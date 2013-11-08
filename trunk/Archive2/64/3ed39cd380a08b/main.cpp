#include <string>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

struct O
{
    O(){
        cout << "DEFAULT" << endl;
    }
    
    O(const O&) {
        cout << "COPY" << endl;
    }
    
    O& operator=(const O&){
        cout << "COPY" << endl;
    }
    
    ~O()
    {
        std::cout << "~O()\n";
    }
};

struct wrapper
{
    O const& val;
    
    ~wrapper()
    {
        std::cout << "~wrapper()\n";
    }
};

 
int main()
{
    std::cout << "case 1-----------\n";
    {
        auto&& a = wrapper{O()};
        std::cout << "end-scope\n";
    }
    std::cout << "case 2-----------\n";
    {
        auto a = wrapper{O()};
        std::cout << "end-scope\n";
    }
    return 0;
}