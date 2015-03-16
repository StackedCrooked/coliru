#include <iostream>
#include <numeric>
#include <type_traits>
#include <vector>


    template<typename ... Args> struct Base;

    template<typename T>
    struct Base<T>
    {
        using ValueType = T;

        virtual ValueType operator()() const = 0;
    };

    template<typename T, typename Derived>
    struct Base<T, Derived> : public Base<T>
    {
        using ValueType = typename Derived::ValueType;
              
        virtual ValueType operator()() const override final
        {
             return static_cast<Derived const&>(*this).apply();
        }
    };


    template<typename T>
    struct Start : public Base<T, Start<T> >
    {
        using ValueType = T;
        
        auto apply() const
        {
             return ValueType();
        }
    };
    
    template<typename Derived>
    struct FirstTransformation : public Base<double, FirstTransformation<Derived> >
    {
        FirstTransformation(Derived const& _derived) : derived(_derived) {}
        auto apply() const
        {
            //return derived()+2;
            return derived()+11.1;
        }
        Derived const& derived;
    };
    template<typename Derived>
    auto applyFirstTransformation(Derived const& derived)
    {
        return FirstTransformation<Derived>(derived);
    }
    


int main()
{
    Start<int> start;
    std::cout<<start()<<std::endl;
    
    std::cout<<applyFirstTransformation(start)()<<std::endl;
}
