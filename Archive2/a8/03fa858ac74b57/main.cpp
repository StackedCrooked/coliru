#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <tuple>

struct SomeParameter
{
public:
    virtual ~SomeParameter() = default;
    virtual size_t GetHashCode() { return typeid(this).hash_code(); }
};

struct InheritedParameter : public SomeParameter
{
};

template<class ...T>
class ParamWrapper : public SomeParameter
{
public:
    std::tuple<T...> Value;
    
    ParamWrapper(T&&... values)
        : Value(values...)
    {
    }
};

class Container
{
private:
    std::unordered_map<size_t, SomeParameter> m_items;
    
public:
    template<class T>
    void Add(T value)
    {
        m_items[value.GetHashCode()] = value;
    }
    
    template<class T>
    SomeParameter& Resolve()
    {
        return m_items[typeid(T).hash_code()];
    }
};

class Injector
{
private:
    Container   m_container;
    
public:
    template<class T, class ... TParam>
    T Build()
    {
        return T((TParam)m_container.Resolve<TParam>()...);
    }
    
    template<class T>
    void Add(T value)
    {
        m_container.Add(value);
    }
};

class BuildMe
{
private:
    SomeParameter&  parameter;
    int             parameter2;
    
public:
    BuildMe(SomeParameter& param, ParamWrapper<int>& param2)
        : parameter(param), parameter2(std::get<0>(param2.Value))
    {
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const BuildMe& instance)
    {
        return stream << "Param2: " << instance.parameter2 << std::endl;
    }
};

int main()
{
    Injector injector;
    injector.Add<ParamWrapper<int>>(7);
    injector.Add<SomeParameter>({});
    
    auto built = injector.Build<BuildMe, SomeParameter&, ParamWrapper<int>&>();
    
    std::cout << built;
}
