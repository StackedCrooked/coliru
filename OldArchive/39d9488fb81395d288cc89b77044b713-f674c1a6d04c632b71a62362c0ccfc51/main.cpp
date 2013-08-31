#include <functional>

typedef int(*inconvertable)();

int f(int) {return 0;}
int g(short) {return 0;}
int h(inconvertable) {return 0;}
short i(int) {return 0;}
inconvertable j(int) {return 0;}

//expects "int(int)", allows conversions
template<class T>
auto function(T func, int var) -> decltype(int(func(1)))
{return func(var);}

int main() {
    function(f, 2);
    function(g, 3);
    //function(h, 4); //error: no matching function for call to ‘function(int (&)(inconvertable), int)’
    function(i, 5);
    //function(j, 6); //error: no matching function for call to ‘function(int (* (&)(int))(), int)’
}