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
    typedef typename stored_type<T>::type U;
    bob() { std::cout << std::is_same<std::shared_ptr<T>, U>::value << std::endl;};
    std::vector<U> a_map;
    void insert(T t) { a_map.push_back(U{new t});
};

struct foo{};
int main()
{
    
    bob<const int> a;
    bob<int> b;
    bob<foo> c;
    
    int n = 4;
    const int m = 5;
    
    a.insert (m);
    b.insert (n);
}
