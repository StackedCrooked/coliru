#include <cassert>

enum class Paths: int
{
    PATH_ONE = 11,
    PATH_TWO = 22,    
};

template <Paths pathValue>
class Foo //: public CSingleton<Foo> <-- i dont have CSingleton, this is still a template
{
public:
    Foo()
    {
    }

    int myValue = static_cast<int>(pathValue);
};

int main()
{
    assert(11 == Foo<Paths::PATH_ONE>().myValue);
    assert(22 == Foo<Paths::PATH_TWO>().myValue);
    
    return 0;
}