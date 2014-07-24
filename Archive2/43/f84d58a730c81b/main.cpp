#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

template<class ...ArgsInit>
class ObjectPoolImpl
{
public:

    template<class ...Args>
    ObjectPoolImpl(Args&& ... args){
        cout << "Call ctr" << endl;
    }

     ~ObjectPoolImpl(){
         cout << "Call dstr" << endl;
    }
};


template<class ... Args>
ObjectPoolImpl<Args...> objectPool(Args&& ... args){
    cout << "call "<<endl;
    using t = ObjectPoolImpl<Args...>;
    return t(args...);
    //return t(1,2,3);      // not due to initializer list
}

int main(){
    auto pool = objectPool(100, true, false, 500, 600, 700);    // What a hell is going on here????
    
    //ObjectPoolImpl<int, int, int> p2(100, false, 900);        // but all ok with this.
}