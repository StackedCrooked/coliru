#include <iostream>
using namespace std;

bool something_wrong = true;
enum X1 {};
enum X2 {};

void bar() {
    cout << "bar starts" << endl;
    if (something_wrong)
        throw X1();
    cout << "bar ends" << endl;
}

void foo() {
    cout << "foo starts" << endl;
    try {
        bar();
    }
    catch (...) {
        cout << "caught any exception in foo" << endl;
        throw;
    }    
    cout << "foo ends" << endl;
}

int main()
{
    try {
        cout << "try starts" << endl;
        foo();
        cout << "try ends" << endl;
    }
    catch (X1 dummy) {
        cout << "caught X1 in main" << endl;
    }    
    catch (X2 dummy) {
        cout << "caught X2 in main" << endl;
    }    
}
