#include <iostream>
#include <ostream>

using namespace std;

class thing  {
private:
        const char *foo;
public:
        thing(){   foo="asd";   }
        const char* getString() const {   return foo;   }
};

template<typename T, class = decltype(std::cout<<std::declval<T>().getString())>
ostream& operator<<(ostream &out, T const &abc){
    out<<abc.getString();
    return out;
}

int main(){
    thing test;
    cout<<test << 3;
    return 0;
}