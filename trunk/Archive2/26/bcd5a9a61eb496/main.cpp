#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template <typename Types>
struct temp{
    typedef typename Types::typeA typeA;

    static typeA foo(){
        cout << "foo" << endl;
        return 0;
    }
    static typename Types::typeB bar(){
        cout << "bar" << endl;
        return 0;
    }
};

typedef int typeA;
typedef long typeB;

struct Types{
    typedef ::typeA typeA;
    typedef ::typeB typeB;
};


void test(){
    temp<Types>::foo();
    temp<Types>::bar();
}


int main(){

}

