#include <iostream>
#include <vector>
#include <memory>
template <typename T>
struct stored_type{
  typedef std::shared_ptr<T> type;

};

template<>
struct stored_type<int>{
  typedef int type;
};

template <typename T, typename U = typename stored_type<T>::type>
struct bob 
{
    bob() { std::cout << std::is_same<std::shared_ptr<T>, U>::value << std::endl;};
    std::vector<U> a_map;
};

struct foo{};
int main()
{
    
    bob<const int> a;
    bob<int> b;
    bob<foo> c;    
}
