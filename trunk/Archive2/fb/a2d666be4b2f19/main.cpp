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

template <typename T>
struct bob 
{
    bob() { std::cout << std::is_same<std::shared_ptr<T>, typename stored_type<T>::type>::value << std::endl;};
    std::vector<typename stored_type<T>::type> a_map;
};

struct foo{};
int main()
{
    bob<int> b;
    bob<foo> c;    
}
