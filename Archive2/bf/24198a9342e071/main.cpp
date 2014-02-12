#include <iostream>

using namespace std;

class T {
  public:
    T() {
        cout << "constructor" << endl;
    }

    T(T const& other) {
        cout << "copy constructor" << endl;
    }
    
    ~T() {
        cout << "destructor" << endl;
    }
    
    T & operator=(T const& other) {
        cout << "assigment" << endl;
        return *this;
    }
};

void noret(T a) {
    cout << "innoret" << endl;
}

T ret(T a) {
    cout << "inret" << endl;
    return a;
} 

T refret(T const& a) {
    cout << "inrefret" << endl;
    return a;
}

int main() {
    T a;

    cout << "=============== 1" << endl;
    T b = ret(a);

    cout << "=============== 2" << endl;
    T d;
    d = T();

    cout << "=============== 3" << endl;
    b = ret(T());
    
    cout << "=============== 4" << endl;
    T c;

    cout << "=============== 5" << endl;
    c = refret(b);

    cout << "=============== 6" << endl;
    T e;
    noret(e);
    noret(T());

    return 0;
}
