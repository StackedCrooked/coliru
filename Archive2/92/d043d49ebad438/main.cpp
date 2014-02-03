#include <iostream>
#include <map>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/make_shared.hpp>

namespace fun
{
    // An undefined type, used as an argument placeholder in our DSL
    struct _;
     
    template<typename Signature>
    struct composed_fn;
     
    // An improved composed_fn template that uses the TR1 result_of
    // protocol to declare and compute function return types.
    template<typename Fn1, typename F>
    struct composed_fn<Fn1(F)>
    {
        // Recursively compose all nested function types to build
        // a composed function object out of them.
        typedef composed_fn<F> Fn2;
     
        explicit composed_fn(Fn1 f1 = Fn1(), Fn2 f2 = Fn2())
          : fn1(f1), fn2(f2)
        {}
     
        template<typename Signature>
        struct result;
     
        template<typename This, typename T>
        struct result<This(T)>
        {
            typedef typename boost::result_of<Fn2(T)>::type U;
            typedef typename boost::result_of<Fn1(U)>::type type;
        };
        
        template<typename T>
        typename result<composed_fn(T)>::type
        operator()(T x) const
        {
            return fn1(fn2(x));
        }
     
        Fn1 fn1;
        Fn2 fn2;
    };
     
    // This specialization ends the recursion begun on line 14.
    // "composed_fn<Fn(_)> fn; fn(3);" is equivalent to "Fn fn; fn(3);"
    template<typename Fn>
    struct composed_fn<Fn(_)> : Fn {};
    
     
    // TRICKSY!!! Read below for why this specialization is necessary.
    template<typename Fn>
    struct composed_fn<Fn *> : composed_fn<Fn> {};

}

template <typename Map>
struct get_value
{
    typedef typename Map::value_type    value_type;
    typedef typename Map::mapped_type   result_type;
    result_type& operator()(value_type& v) const {return v.second;}
    const result_type& operator()(const value_type& v) const {return v.second;}
};

template <typename Map>
struct get_key
{
    typedef typename Map::value_type    value_type;
  typedef typename Map::key_type   result_type;
  const result_type& operator()(const value_type& v) const {return v.first;}
};

struct deref
{
    template <typename Sig>
    struct result;
    
    template <typename This, typename It>
    struct result<This(It)>
    {
        typedef typename boost::iterator_reference<typename boost::remove_reference<It>::type>::type type;
    };
    
    template <typename It>
    typename result<const deref(It)>::type operator()(It iter) const
    {
        return *iter;
    }
};

struct increment_int
{
    typedef int result_type;
    
    result_type operator()(int val) const
    {
        return ++val;
    }
};

struct duplicate_string
{
    typedef std::string result_type;
    
    result_type operator()(const std::string& val) const
    {
        return val+val;
    }
};

int main()
{
    typedef std::map<std::string, int* > PtrMap;
    PtrMap ptr_map;
    int foo = 1;
    int bar = 2;
    ptr_map["foo"]=&foo;
    ptr_map["bar"]=&bar;
    
    using fun::_;
    {
    typedef fun::composed_fn<increment_int(deref(get_value<PtrMap>(_)))> deref_map_value_and_increment;
    
    typedef boost::transform_iterator<deref_map_value_and_increment,PtrMap::iterator> transformed_iterator;
    
    transformed_iterator begin(ptr_map.begin(),deref_map_value_and_increment()), end(ptr_map.end(),deref_map_value_and_increment());
    
    std::copy(begin,end,std::ostream_iterator<int>(std::cout," ")); 
    }
    //-------
    {
    typedef fun::composed_fn<duplicate_string(get_key<PtrMap>(_))> duplicate_key;
    
    typedef boost::transform_iterator<duplicate_key,PtrMap::iterator> transformed_iterator;
    
    transformed_iterator begin(ptr_map.begin(),duplicate_key()), end(ptr_map.end(),duplicate_key());
    
    std::copy(begin,end,std::ostream_iterator<std::string>(std::cout," ")); 
    }
}
