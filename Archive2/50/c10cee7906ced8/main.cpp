#include <iostream>

using namespace std;

void f(int) {
    cout << __PRETTY_FUNCTION__ << endl;
}
void f(long) {
    cout << __PRETTY_FUNCTION__ << endl;
}
void f(bool) {
    cout << __PRETTY_FUNCTION__ << endl;
}
void f(void*) {
    cout << __PRETTY_FUNCTION__ << endl;
}

int main(int, char*[]) {
    f(1 == 0);
    f(0);
    f(NULL);
    f(nullptr);
    return 0;
}