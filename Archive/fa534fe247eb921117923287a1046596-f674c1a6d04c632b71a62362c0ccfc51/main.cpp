#include <vector>

template <class T>
class foo{
  std::vector<T> vec;  
};

int main(){
 foo<int> obj;
 return 0;
}