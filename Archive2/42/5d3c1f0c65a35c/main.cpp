#include <iostream>
#include <functional>

using namespace std;

class C {
public: 
    C() { cout << "CREATING" << endl; }
    C(const C&) { cout << "COPY C "<< endl; };
    C(C&&) { cout << "MOVE C " << endl; };
    ~C() { cout << "DELETING"<< endl; }
    C& operator =(const C&) {
        cout << "COPY A " << endl; return *this;
    };
    C& operator =(C&&) {
        cout << "MOVE A" << endl; return *this;
    };
    void operator ()() const { cout << "CALLING" << endl; }
};

int main(int argc, char *argv[]) {
    function<void()> f{std::bind( &C::operator(), std::ref(C()) )};
    f();
    return 0;
}