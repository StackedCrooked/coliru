#include <iostream>
#include <ostream>

using namespace std;

class thing  {
private:
        const char *foo;
public:
        thing(){   foo="asd";   }
        const char* getString(){   return foo;   }
};

template<typename T>
ostream& operator<<(ostream &out, T &abc){
    out<<abc.getString();
    return out;
}

int main(){
    thing test;
    cout<<test;
    return 0;
}