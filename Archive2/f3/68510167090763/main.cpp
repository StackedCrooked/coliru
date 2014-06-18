#include <iostream>
#include <string>
#include <vector>

namespace client
{
    template<typename T>
    struct scalar
    {
        typedef T result_type;
        
        scalar(T t) :
            t_(t)
        {}
        
        T get() const
        { 
            return t_; 
        }
        
        T t_;
    };
    
    template<
        typename T1, 
        typename T2
    >
    struct add
    {
        typedef 
        typename
        T1::result_type result_type;
        
        add(
            const T1& t1, 
            const T2& t2
        ) 
            : t1_(t1), t2_(t2)
        {}
        result_type get() const
        {
            return 
                t1_.get() + 
                t2_.get();
        }
        
        operator result_type ()
        {
            return get();
        }           
        
        const T1& t1_;
        const T2& t2_;
    };
    
    template<
        typename T1,
        typename T2
    >
    add<T1, T2> 
    operator + (
        const T1& l,
        const T2& r
    )
    {
        return add<T1,T2>(l, r);
    }
}

int main()
{
    using namespace client;
    
    scalar<int> s1(2);
    scalar<int> s2(5);
    scalar<int> s3(1);
    
    int result = s1 + (s2 + s3);
    std::cout << result;
}
