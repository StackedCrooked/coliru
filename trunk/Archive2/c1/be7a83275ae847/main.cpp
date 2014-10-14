#include <iostream>
#include <vector>
#include <string>
using namespace std;

class S {
    std::string ss;
    private: S() {
        ss = "ub ub ub ub ub ub ub ub ";
        cout << "S::S" << endl;
    }

    public: static S* instance() {
        static S* i;
        if(i == NULL) {
            cout << "Create S" << endl;
            i = new S;
        }
        return i;
    }

    public: virtual ~S() {
        cout << "S::~S" << endl;
    }

    public: void a() {
        cout << "S::a" << ss << endl;
    }
};

int main() {
        S::instance()->a();
        // delete pointer to instance (no reason, because I'm curious)
        delete S::instance();    
    for ( int n = 0; n < 100; ++n ){
        std::vector<char> avec(n);
        // call some method
        S::instance()->a();
    }

    return 0;
}