#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/utility/result_of.hpp>

namespace detail{
template<class F, class S>
struct composed{
    template<class T>
    struct result{
        typedef typename boost::result_of<F(T&)>::type result1;
        typedef typename boost::result_of<S(result1)>::type type;
    };
    
    template<class T>
    typename result<T>::type operator()(T& v) const
    {
        F first; S second;
        return second(first(v));
    }
    
    template<class T>
    typename result<T const>::type operator()(T const& v) const
    {
        F first; S second;
        return second(first(v));
    }
};

struct ignore{}; // because there's no 'mpl:fold1' and we want all traits in an 'mpl::vector'

struct compose{
    template<class First, class Second>
    struct apply{
        typedef detail::composed<First, Second> type;
    };
    
    template<class Second>
    struct apply<ignore, Second>{
        typedef Second type;
    };
};
} // detail::

template<class Seq>
struct compose_traits{
    typedef typename boost::mpl::fold<Seq, detail::ignore, detail::compose>::type type;
};

template<int N>
struct add{
    typedef int result_type;
    int operator()(int v) const{ return v + N; }
};

template<int N>
struct mul{
    typedef int result_type;
    int operator()(int v) const{ return v * N; }
};

#include <iostream>

int main(){
    typedef boost::mpl::vector<add<5>, mul<10>, add<-20>, mul<-2> > seq;
    typedef compose_traits<seq>::type result;
    
    std::cout << result()(5);
}