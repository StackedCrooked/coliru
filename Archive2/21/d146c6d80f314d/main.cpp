#include <iostream>
#include <functional>
#include <tuple>
#include <map>
#include <unordered_map>

template <template <typename, typename, typename, typename> class M, 
          typename R, typename... Args>
class memoizer_ord
{

private:
    using value_type = R;
    using key_type   = std::tuple<Args...>;

    M<key_type, value_type, 
      std::less<key_type>, 
      std::allocator<std::pair<const key_type, value_type>>> mem;

    std::function<R(Args...)> func;
    
public:

    memoizer_ord(std::function<R(Args...)> f)
        : func(f)
    { }

    R operator()(Args&&... args) 
    {
        auto tup = std::make_tuple(args...);
        auto it = mem.find(tup);
        if(it != mem.end()) {
            std::cout << "Found\n";
            return it->second;
        }
        std::cout << "Not found\n";
        auto value = func(args...);
        auto inserted = mem.emplace(std::move(tup), std::move(value));
        
        return inserted.first->second;
    }
};

template <class T>
inline void hash_combine(std::size_t& seed, T const& v)
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl
{
  static void apply(size_t& seed, Tuple const& tuple)
  {
    HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
    hash_combine(seed, std::get<Index>(tuple));
  }
};

template <class Tuple>
struct HashValueImpl<Tuple,0>
{
  static void apply(size_t& seed, Tuple const& tuple)
  {
    hash_combine(seed, std::get<0>(tuple));
  }
};

template <template <typename, typename, typename, typename, typename> class M,
          typename R, typename... Args>
class memoizer_unord
{

private:
    using value_type = R;
    using key_type   = std::tuple<Args...>;

    struct hash_tuple
    {
        std::size_t operator()(const std::tuple<Args...>& tup) const
        {
            size_t seed = 0;                             
            HashValueImpl<std::tuple<Args...> >::apply(seed, tup);    
            return seed;     
        }
    };

    M<key_type, value_type, 
      hash_tuple,
      std::equal_to<key_type>,
      std::allocator<std::pair<const key_type, value_type>>> mem;

    std::function<R(Args...)> func;
    
public:

    memoizer_unord(std::function<R(Args...)> f)
        : func(f)
    { }

    R operator()(Args&&... args) 
    {
        auto tup = std::make_tuple(args...);
        auto it = mem.find(tup);
        if(it != mem.end()) {
            std::cout << "Found\n";
            return it->second;
        }
        std::cout << "Not found\n";
        auto value = func(args...);
        auto inserted = mem.emplace(std::move(tup), std::move(value));
        
        return inserted.first->second;
    }
};

int main()
{
    auto f = [](int i, int j) { return i + j; };
    memoizer_unord<std::unordered_map, int, int, int> m(f);
    auto i = m(1, 1);
    auto j = m(1, 1);
    std::cout << i << "\n";
    std::cout << j << "\n";
}