#include <new>

struct A{
    A(){
        throw 0;
    }  
};

int main(){
    try{
        A* a = new A;
    }
    catch(std::bad_alloc&){}
}
