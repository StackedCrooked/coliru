#include <type_traits>

template<typename T, T &object, typename... Args>
struct Functor
{
    template<float (T::*function)(Args...), Args... args>
    struct Inner
    {
        float operator()() const
        {
            return (object.*function)(args...);
        }
    };
};

class Object
{
public:

    float someFunction()
    {
        return {};
    }

    float someFunctionWithArgument(int)
    {
        return {};
    }
};

Object object;

Functor<Object, object>::template Inner<&Object::someFunction> functor1;
Functor<Object, object, int>::template Inner<&Object::someFunctionWithArgument, 1> functor2;

int main()
{

}