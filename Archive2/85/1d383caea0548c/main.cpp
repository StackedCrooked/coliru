#include <iostream>
#include <memory>

using namespace std;

class MBase {
    public:
        virtual ~MBase() { cout << "Base destructor\n" << endl; }
};

class MF: public MBase {
    public:
        ~MF() { cout << "MF Destructor" << endl; }
};

class MS: public MBase {
    public:
        ~MS() { cout << "MS Destructor" << endl;}
};

int main() {

    unique_ptr<MBase> ptr1 = unique_ptr<MF>(new MF());
    unique_ptr<MBase> ptr2 = unique_ptr<MS>(new MS());

    return 0;
}