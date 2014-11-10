#include <iostream>
using namespace std;
#include <vector>

class foo{
public:

    operator std::vector<char>(){
        return std::vector<char>();
    }

    template <typename T>
    explicit operator std::vector<T>(){
        return std::vector<T>();
    }

};


int main(int argc, char* argv[]) {


    foo x;
    
    std::vector<char> c = x;
    std::vector<int> v = (std::vector<int>)x;


}
