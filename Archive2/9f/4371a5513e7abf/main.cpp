
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Test {};

template <>
class Test {
public:
    void print(){ cout << "Hello, World!" << endl;
};

int main(int argc, char* argv[])
{
    
    Test a;
    a.print();
    
	return 0;
}