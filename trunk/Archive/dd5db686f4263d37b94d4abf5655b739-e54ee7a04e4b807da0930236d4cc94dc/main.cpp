#include <memory>

template<class T>
struct maybe_deleter{
  bool _delete;
  explicit maybe_deleter(bool doit = true) : _delete(doit){}
  
  void operator()(T* p) const{
    if(_delete) delete p;
  }
};

template<class T>
using set_unique_ptr = std::unique_ptr<T, maybe_deleter<T>>;

template<class T>
set_unique_ptr<T> make_find_ptr(T* raw){
    return set_unique_ptr<T>(raw, maybe_deleter<T>(false));
}

#include <iostream>
#include <unordered_set>

int main(){
    int* raw = new int(42);
    std::unordered_set<set_unique_ptr<int>> myset;
    myset.insert(set_unique_ptr<int>(raw));
    
    auto it = myset.find(make_find_ptr(raw));
    std::cout << std::boolalpha << (it != myset.end()) << " " << **it;
}