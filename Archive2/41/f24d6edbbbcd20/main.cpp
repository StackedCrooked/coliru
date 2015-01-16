#include <iostream>
using namespace std;

class Test {
    int testInt = 3;
    public:
        friend void getTestInt(Test);
};

void getTestInt(Test a) {
    cout << "test int: " << a.testInt;
}

int main ()
{
    Test testObject;
    getTestInt(testObject);
}