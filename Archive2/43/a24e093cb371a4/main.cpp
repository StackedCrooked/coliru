#include <type_traits>
#include <boost/optional.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

template<typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

template<class T> class Functor;

template<typename F, typename T>
auto fmap(F f, T const& t)
{
    return Functor<T>(t).fmap(f);
}

template<typename T> class Applicative;

template<typename M, typename T>
auto pure(T&& t)
{
    return Applicative<M>::pure(std::forward<T>(t));
}

template<typename F, typename T>
auto ap(F f, T const& t)
{
    return Applicative<T>(t).ap(f);
}

template<class T> class Monad;

template<typename T, typename F>
auto mbind(T const& t, F f)
{
    return Monad<T>(t).bind(f);
}

template<typename T, typename F>
auto operator >>= (T const& t, F f)
{
    return mbind(t, f);
}

template<typename T, typename F>
auto operator <<= (F f, T const& t)
{
    return mbind(t, f);
}

template<typename T, typename U>
auto operator >> (T const& t, U const& u)
{
    return mbind(t, [&u] (auto const&) { return u; });
}

template<typename T>
class Functor<boost::optional<T>>
{
public:
    Functor(boost::optional<T> const& o) : _o{o} { }
    template<typename F>
    auto fmap(F f)
    {
        using value_type = remove_reference_t<decltype(f(*_o))>;
        boost::optional<value_type> result;
        if (_o) { result = f(*(this->_o)); }
        return result;
    }
protected:
    boost::optional<T> const& _o;
};

template<typename T>
class Applicative<boost::optional<T>> : public Functor<boost::optional<T>>
{
public:
    Applicative(boost::optional<T> const& o) : Applicative::Functor{o} { }
    template<typename AF>
    auto ap(AF af)
    {
        using value_type = remove_reference_t<decltype((*af)(*(this->_o)))>;
        boost::optional<value_type> result;
        if (this->_o && af) { result = (*af)(*(this->_o)); }
        return result;
    }
    static boost::optional<T> pure(T t)
    {
        return std::move(t);
    }
};

template<typename T>
class Monad<boost::optional<T>> : public Applicative<boost::optional<T>>
{
public:
    Monad(boost::optional<T> const& o) : Monad::Applicative{o} { }
    template<typename F>
    auto bind(F f)
    {
        using result_type = typename decltype(f(*(this->_o)))::value_type;
        using value_type = remove_reference_t<result_type>;
        boost::optional<value_type> result;
        if (this->_o) { result = f(*(this->_o)); }
        return result;
    }
};

template<typename T> 
class Functor<std::vector<T>>
{
public:
    Functor(std::vector<T> const& v) : _v{v} { }
    template<typename F>
    auto fmap(F f)
    {
        using value_type = remove_reference_t<decltype(f(_v.front()))>;
        std::vector<value_type> res;
        transform(begin(_v), end(_v), std::back_inserter(res), f);
        return res;
    }
protected:
    std::vector<T> const& _v;
};

template<typename T> 
class Applicative<std::vector<T>> : public Functor<std::vector<T>>
{   
public:
    Applicative(std::vector<T> const& v) : Applicative::Functor{v} { }
    template<typename AF>
    auto ap(AF af)
    {
        auto&& v = this->_v;
        using result_type = decltype((af.front())(v.front()));
        using value_type = remove_reference_t<result_type>;
        std::vector<value_type> result;
        for (auto&& f : af)
        {
            transform(begin(v), end(v), std::back_inserter(result), f);
        }
        return result;
    }
    static std::vector<T> pure(T t)
    {
        return { std::move(t) };
    }
};

template<typename T> 
class Monad<std::vector<T>> : public Applicative<std::vector<T>>
{   
public:
    Monad(std::vector<T> const& v) : Monad::Applicative{v} { }
    template<typename F>
    auto bind(F f)
    {
        auto&& v = this->_v;
        using result_type = typename decltype(f(v.front()))::value_type;
        using value_type = remove_reference_t<result_type>;
        std::vector<value_type> result;
        for (auto&& x : v)
        {
            auto vx = f(x);
            result.insert(end(result), begin(vx), end(vx));
        }
        return result;
    }
};

template<typename T>
void print(boost::optional<T> const& o)
{
    if (o)
    {
        std::cout << "Just " << *o;
    }
    else
    {
        std::cout << "Nothing";
    }
}

template<typename T>
void print(std::vector<T> const& v)
{
    std::cout << "{ ";
    std::copy(begin(v), end(v), std::ostream_iterator<T>(std::cout, " "));
    std::cout << "}";
}

template<typename T>
void println(T const& t)
{
    print(t);
    std::cout << std::endl;
}

#define END_1 };
#define END_2 END_1 };
#define END_3 END_2 };
#define END_4 END_3 };
#define END_5 END_4 };
#define END_6 END_5 };
#define END_7 END_6 };
#define END_8 END_7 };
#define END_9 END_8 };
#define END_10 END_9 };

#define END(x) END_ ## x

#define DO 
#define BIND(x, expr) \
    expr >>= [&] (auto&& x) { return 

int main()
{
    auto replicate3 = [] (int x) -> std::vector<std::string>
    { 
        return {std::to_string(x), 
                std::to_string(x),
                std::to_string(x)}; 
    };

    std::vector<int> v{1, 2, 3};
    println(mbind(v, replicate3));

    auto twice = [] (int o) { return boost::optional<int>{o * 2}; };
    boost::optional<int> o{42};
    println(o >>= twice);

    boost::optional<int> nothing;
    println(nothing >>= twice);

    println(pure<boost::optional<int>>(1337));
    println(pure<std::vector<int>>(1337));

    auto thrice = [] (int o) { return boost::optional<int>{o * 3}; };
    println((o >>= thrice) >>= twice);
    println(thrice <<= twice <<= o);

    boost::optional<std::string> os{"text"};
    println(o >> os);

    auto f = [] (auto x) { return x + x; };
    println(fmap(f, v));

    std::vector<std::string> vs{"Hey", "you", "there!"};
    println(fmap(f, vs));

    println(fmap(f, os));
    println(fmap(f, nothing));

    std::vector<std::function<int(int)>> vf = {[] (int x) { return x * 2; }, 
                                               [] (int x) { return x + 3; },
                                               [] (int x) { return x - 5; }};
    println(ap(vf, v));

    boost::optional<std::function<int(int)>> of{[] (int x) { return x * x; }};
    boost::optional<std::function<int(int)>> fnothing;
    println(ap(of, o));
    println(ap(of, nothing));
    println(ap(fnothing, o));

    auto fx =
        DO
            BIND(x, o)
            BIND(x1, twice(x))
            BIND(x2, thrice(x1))
            boost::optional<int>(x2);
        END(3)

    println(fx);
    
    auto fy =
        DO
            BIND(x, v)
            BIND(y, replicate3(x))
            BIND(z, vs)
            std::vector<std::string>{ "(" + y + "," + z + ")\n" }; 
        END(3)
        
    println(fy);
}