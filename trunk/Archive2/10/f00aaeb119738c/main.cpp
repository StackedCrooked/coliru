#include <tuple>

template <typename ... Child>
class Tpl
{
public:
    Tpl() {}
    Tpl(Child ...args) : child(args...)
    {}

    template <typename T>
    T& Get()
    {
        return std::get<T>(child);
    }

    template <typename T>
    const T& GetConst()
    {
        return std::get<T>(child);
    }
private:
    std::tuple<Child ...> child;
};

template <typename... Ts>
class SomeObject : public Tpl<Ts...>
{
public:
    SomeObject(/*Types ... args*/) /*: child(args...)*/
    {

    }
private:
    int num;        
};

int main()
{
    SomeObject<int, char> s;
}
