#include <iostream> 

using namespace::std;


class X {
    public:
        X() {
            cout << "Default Constructor called " << this << '\n';
            i = 0;
        }


        X(int i) {
            cout << "Parameterized Constructor called " << this << '\n';
            this->i = i;
        }
        X(const X& x) {
            cout << "Copy Constructor called " << this << '\n';
            i = x.getI();
        }
        ~X() {
            cout << "Destructor called " << this << '\n';
        }
        int getI() const {
            return i;
        }
        X func() {
            cout << "Entered func " << this << '\n';
            X x(2);
            return x;
        }
    private:
        int i;
};

int main() {
     X x1;
     X x2 = x1.func();
    cout << "Returned from func\n";    
}
