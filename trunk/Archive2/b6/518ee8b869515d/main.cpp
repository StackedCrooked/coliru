#include <functional>

template< typename T, typename... Arguments>
struct FunctionPtrWrapper
{
    FunctionPtrWrapper(T(*funcIn)(Arguments...), Arguments... args)
    {
        funcPtr=std::bind(funcIn, args...);
    }
    void go()
    {
        funcPtr();
    }
    std::function< T()> funcPtr;
};

void foo(char) {}

int main(){
    FunctionPtrWrapper<void, char> pointerTwo(&foo, 'c');
    pointerTwo.go();

}