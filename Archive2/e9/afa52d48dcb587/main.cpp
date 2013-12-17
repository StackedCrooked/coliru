#include <iostream>

using datum = double;
using std::cout;

struct Variable {
    datum d = 2.0;
};

struct Method {
    Variable v;    
};

struct Class {
    Method m;
};

static Class c;

class Kastje {    
public:
    explicit Kastje(const datum& frank){
        this->frank = frank;    
    };
    inline datum laadje();
private:
    datum frank;
};

inline
datum Kastje::laadje() {
    return frank * c.m.v.d;    
}

int main() {
    std::cout << Kastje(3.0).laadje();
}