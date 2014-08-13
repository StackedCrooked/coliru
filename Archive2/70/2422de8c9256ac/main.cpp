#include <type_traits>
class Var
{
public:
    
    template <typename T, typename std::enable_if<std::is_same<int, T>::value>::type * = nullptr>
    operator T () const
    { return T(); }

};

int main()
{
    Var v;
    switch (v)
    { }
}