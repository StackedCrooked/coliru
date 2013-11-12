#include <vector>
#include <utility>
#include <iterator>
#include <type_traits>
#include <boost/optional.hpp>
#include <boost/iterator/iterator_facade.hpp>

template<class T>
using Invoke = typename T::type;

template<class T>
using Decay = Invoke<std::decay<T>>;

template<class T>
using ResultOf = Invoke<std::result_of<T>>;

template<class T>
using ValueType = typename T::value_type;

template<class T>
struct identity{ using type = T; };

template<class T, class U>
struct rebind : identity<T>{};

template<class T, class A, class U>
struct rebind<std::vector<T, A>, U> : identity<std::vector<U, A>>{};

template<class T, class U>
using Rebind = Invoke<rebind<T, U>>;

template<class T>
T unwrap(T&& v){ return std::forward<T>(v); }

template<class T>
T& unwrap(std::reference_wrapper<T> v){ return v.get(); }

template<class T>
using Unwrap = decltype(unwrap(std::declval<T>()));

template<class F, class O>
struct mapped_t{
    
private:
    using origin_type = Unwrap<O>;
    using origin_iterator = typename Decay<origin_type>::iterator;
    
    using value_type = Decay<ResultOf<F&(typename Decay<origin_type>::reference)>>;
    
    struct placeholder{};
    using inner_value_type = boost::optional<value_type>;
    using container_type = Rebind<Decay<origin_type>, inner_value_type>;
    using inner_iterator = typename container_type::iterator;
    
    F _f;
    origin_type _o;
    container_type _c;
    
public:
    mapped_t(F f, O&& o) : _f(f), _o(unwrap(std::forward<O>(o))), _c(_o.size()){}
    
    value_type& front(){ return *begin(); }
    
    struct iterator
        : boost::iterator_facade<iterator, value_type, boost::random_access_traversal_tag>
    {
        F* f;
        inner_iterator self;
        origin_iterator origin;
        
        iterator(F* f, inner_iterator s, origin_iterator o) : f(f), self(s), origin(o){}
        
        value_type& dereference() const{
            if (!*self)
                *self = (*f)(*origin);
            return **self;
        }
        bool equal(iterator const& other) const{ return self == other.self; }
        void increment(){ ++self; ++origin; }
    };
    
    iterator begin(){ return {&_f, _c.begin(), _o.begin()}; }
    iterator end(){ return {nullptr, _c.end(), _o.end()}; }
};

template<class F, class C>
mapped_t<F, C> map(F f, C&& c){
    return {f, std::forward<C>(c)};
}

#include <iostream>

int main(){
    std::vector<int> v{1,2,3,4};
    auto v2 = map([](int i) -> int{ std::cout << "foo: "; return i * 2; }, v);
    for(auto e : v2)
        std::cout << e << "\n";
    for(auto e : v2)
        std::cout << e << "\n";
}