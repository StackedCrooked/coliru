#include <type_traits>
#include <iostream>

struct fuzzy_base {};

struct fuzzy_var : fuzzy_base
{
    int value;
    
    explicit fuzzy_var(int v) : value(v) {}
    
    int eval() const { return value; }
};

template<typename L,typename R>
struct fuzzy_or : fuzzy_base
{
    L l;
    R r;
    
    fuzzy_or( const L& l, const R& r ) : l(l), r(r) {}
    
    int eval() const { return l.eval() | r.eval(); }
};

template<typename L,typename R>
struct fuzzy_and : fuzzy_base
{
    L l;
    R r;
    
    fuzzy_and( const L& l, const R& r ) : l(l), r(r) {}

    int eval() const { return l.eval() & r.eval(); }
};

template<typename T>
struct fuzzy_negate : fuzzy_base
{
    T t;
    
    fuzzy_negate( const T& t ) : t(t) {}
    
    int eval() const { return ~t.eval(); }
};

// operators need to be protected with enable_if so they don't match arbitrary types
template<typename T>
typename std::enable_if<std::is_base_of<fuzzy_base,T>::value, fuzzy_negate<T>>::type
operator~(const T& t) { return fuzzy_negate<T>(t); }

template<typename L,typename R>
typename std::enable_if<std::is_base_of<fuzzy_base,L>::value && std::is_base_of<fuzzy_base,R>::value, fuzzy_or<L,R>>::type
operator|(const L& l, const R& r) { return fuzzy_or<L,R>(l,r); }

template<typename L,typename R>
typename std::enable_if<std::is_base_of<fuzzy_base,L>::value && std::is_base_of<fuzzy_base,R>::value, fuzzy_and<L,R>>::type
operator&(const L& l, const R& r) { return fuzzy_and<L,R>(l,r); }

int main()
{
    fuzzy_var a(42),b(24),c(1),d(0);

    std::cout << a.eval() << std::endl;

    std::cout << (a&b).eval() << std::endl;

    auto x = (a&b)|(c&~d);
    std::cout << x.eval() << std::endl;
}
