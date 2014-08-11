#include <iostream>
using namespace std;

class foo{
public:
    foo(){}
    foo(foo&&){
        cout << "move constructor" << endl;
    }
    foo(const foo&){
        cout << "copy constructor" << endl;
    }
    void operator=(foo&&){
        cout << "move assignment" << endl;
    }
    void operator=(const foo&){
        cout << "copy assignment" << endl;
    }
};


int main(int argc, char* argv[]) {

    try{
        foo e;
        throw std::move(e);
    } catch (...){
    }

    system("pause");
}
