#include <iostream>
#include <vector>
using namespace std;

class achievement {
public:
    virtual void test() = 0;
};

class tk_king : public achievement {
public:
    void test() {
        cout << "tested for tk_king" << endl;
    }
};

class zr86s_king : public achievement {
public:
    void test() {
        cout << "tested for zr68s_king" << endl;
    }
};

// array of 'achivements'    
//vector<achievement> achievements;

int main() {
    vector<achievement*> a_v;

    a_v.push_back( new tk_king );
    a_v.push_back( new zr86s_king );
    
    for( auto &i : a_v ) {
        i->test();
    }
}