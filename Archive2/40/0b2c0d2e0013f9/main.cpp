#include <vector>
#include <iostream>

template<typename T>
struct MapTtoT { typedef T (type)(const T); };

template<typename F, typename T>
auto map_vec(F&& fnc, const std::vector<T>& source) -> decltype(void(fnc(std::declval<T>())), std::vector<T>())
{
    std::vector<T> dest;
    dest.reserve(source.size());
    for (const auto i : source)
    {
        dest.emplace_back(fnc(i));
    }
    return dest;
}

template<typename T>
struct MapTandVectoT { typedef T (type)(const T, const std::vector<T>&); };

template<typename F, typename T>
auto map_vec(F&& fnc, const std::vector<T>& source) -> decltype(void(fnc(std::declval<T>(), source)), std::vector<T>())
{
    std::vector<T> dest;
    dest.reserve(source.size());
    for (const auto i : source)
    {
        dest.emplace_back(fnc(i, source));
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
    std::vector<int> v {1, 2, 3};
    const auto a = map_vec(foo, v);
    const auto b = map_vec(bar, v);
    
    const AddNum add2(2);
    const auto c = map_vec(add2, v);
    
    const AddNumMulSize add2mulsz(2);
    const auto d = map_vec(add2mulsz, v);
}