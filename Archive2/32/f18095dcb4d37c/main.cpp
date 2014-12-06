#include <vector>
#include <iostream>

template <std::size_t, typename T = void> struct void_t {typedef T type;};

template <typename T>
T& declval();

template<typename F, typename T>
typename void_t<sizeof(declval<F>()(declval<T>())),
       std::vector<T> >::type map_vec(F fnc, const std::vector<T>& source) 
{
    std::vector<T> dest;
    dest.reserve(source.size());
    for (typename std::vector<T>::const_iterator i = source.begin(); i != source.end(); ++i)
    {
        dest.push_back(fnc(*i));
    }
    return dest;
}
template<typename F, typename T>
typename void_t<sizeof(declval<F>()(declval<T>(), declval<const std::vector<T> >())),
       std::vector<T> >::type map_vec(F fnc, const std::vector<T>& source) 
{
    std::vector<T> dest;
    dest.reserve(source.size());
    for (typename std::vector<T>::const_iterator i = source.begin(); i != source.end(); ++i)
    {
        dest.push_back(fnc(*i, source));
    }
    return dest;
}

class AddNum
{
public:
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
    AddNumMulSize(const int num) : num_(num) {}

    int operator()(const int x, const std::vector<int>& v) const
    {
        return (x + num_) * v.size();
    }

private:
    const int num_;
};

int foo(const int) {return 0;}
int bar(const int, const std::vector<int>&) {return 0;}

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    const std::vector<int> a = map_vec(foo, v);
    const std::vector<int> b = map_vec(bar, v);
    
    const AddNum add2(2);
    const std::vector<int> c = map_vec(add2, v);
    
    const AddNumMulSize add2mulsz(2);
    const std::vector<int> d = map_vec(add2mulsz, v);
}
