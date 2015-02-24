#include <vector>
#include <iostream>

// used to overload on types that are not argument types themselves but can be
// deduced from argument types
// e.g.
// expr_check_check<sizeof(type_expression<T>), return_type>::type func(T);
template <std::size_t, typename T = void>
struct expr_check_check {typedef T type;};

// T | T& => T&
// used to create expressions involving a type T without the need for T to be default constructible
template <typename T>
T& declval();


// functors
template<class T>
struct Return
{
    typedef typename T::result_type type;
};

// function pointers
template<class R, class T>
struct Return<R (*)(T)>
{
        typedef R type;
};

// function pointers
template<class R, class T, class U>
struct Return<R (*)(T, U)>
{
        typedef R type;
};

// Use a callable type, F, with return type T to map contents of container type, C, to a std::vector<return type of F>
// F(AtomID) => T
template<typename F, typename C>
typename expr_check_check<sizeof(declval<F>()(declval<int>())), std::vector<typename Return<F>::type> >::type
map_vec(F fnc, const C& source)
{
    std::vector<typename Return<F>::type> dest;
    dest.reserve(source.size());
    for (typename C::const_iterator i = source.begin(); i != source.end(); ++i)
    {
        dest.push_back(fnc(*i));
    }
    return dest;
}

// Use a callable type, F, with return type T to map contents of container type, C, to a std::vector<return type of F>
// Here F takes a second argument, the container itself
// F(AtomID, C) => T
template<typename F, typename C>
typename expr_check_check<sizeof(declval<F>()(declval<int>(), declval<C>())), std::vector<typename Return<F>::type> >::type
map_vec(F fnc, const C& source)
{
    std::vector<typename Return<F>::type> dest;
    dest.reserve(source.size());
    for (typename C::const_iterator i = source.begin(); i != source.end(); ++i)
    {
        dest.push_back(fnc(*i, source));
    }
    return dest;
}

class AddNum
{
public:
    typedef int result_type;

    AddNum(const int num) : num_(num) {}

    int operator()(const int x) const
    {
        return x + num_;
    }

private:
    const int num_;
};

class AddNumMulSize
{
public:
    typedef int result_type;

    AddNumMulSize(const int num) : num_(num) {}

    int operator()(const int x, const std::vector<int>& v) const
    {
        return (x + num_) * v.size();
    }

private:
    const int num_;
};

int foo(const int) {return 0;}
int bar(const int, std::vector<int>) {return 0;}

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // doesn't compile
    const std::vector<int> a = map_vec(foo, v);
    const std::vector<int> b = map_vec(bar, v);

    const AddNum add2(2);
    const std::vector<int> c = map_vec(add2, v);

    const AddNumMulSize add2mulsz(2);
    const std::vector<int> d = map_vec(add2mulsz, v);
}