#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<stdexcept>

/**
 * @brief Decorates an iterator to permit code injection before dereferencing 
 */
template<class T>
struct IteratorDecorator : public T {

  template<class V>
  IteratorDecorator(T iterator, V f) : T(iterator) , m_callback(f) {}

  typename T::value_type & operator*() {
      m_callback();
      return T::operator*();
  }
  
private:
  std::function<void()> m_callback;
};

/**
 * @brief Convenience function just for type deduction 
 */
template<class T, class V>
IteratorDecorator<T> decorate(T iterator, V v) {
  return IteratorDecorator<T>(iterator,v);
}

using namespace std;

int main()
{
  vector<int> ivec {1, 3, 5, 6};
  
  try {
    for_each(ivec.begin(),ivec.end(),[](int& x){ cout << x << endl; } );
    for_each(decorate(ivec.begin(), [](){ cout << "decorated : "; }), 
             decorate(ivec.end()  , [](){}),
             [](int& x){ cout << x << endl; }); 
    for_each(decorate(ivec.begin(), [](){ throw runtime_error("This one throws"); }), 
             decorate(ivec.end()  , [](){}),
             [](int& x){ cout << x << endl; } );
  } catch( exception& e) {
    cout << e.what() << endl;   
  }
    
  return 0;
}