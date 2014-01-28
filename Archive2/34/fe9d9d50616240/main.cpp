#include <functional>
using std::function;
using std::forward;

template<class T> void makeNew(T&& func)
{
    function<void()> p = forward<T>(func);  
}

class POP
{
private:
    function<void()> fu;
public:
    template<typename T> POP(T&& func) : fu(forward<T>(func)) {}
};

void Test(){}


int main()
{
    makeNew(Test); //compiles  (1)
    makeNew(&Test); //compiles (2)
    POP pop(&Test); //compiles (3)
    POP popp(Test); //doesn't compile (4)
}