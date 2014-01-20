#include <boost/range.hpp>
#include <boost/iterator/counting_iterator.hpp>

typedef boost::iterator_range<boost::counting_iterator<int>> int_range;

template <typename T>
class Ref {
    T* p_;    
  public:    
    Ref(T* p) : p_(p) { }
    /* possibly other implicit conversion constructors,
       but no unconstrained template constructors that don't
       use the explicit keyword... */  
    operator T*() const { return p_; }
    operator const T*() const { return p_; }    
};

struct Bar { };

class Foo {    
  public:    
    Foo(int a, char b) { /* ... */ }    
    Foo(int a, const Ref<Bar>& b) { /* ... */ }     
    Foo(int a, const int_range& r) { /* ... */ }     
    template <typename U, typename=typename std::enable_if<
      !std::is_base_of<Ref<Bar>,typename std::decay<U>::type>::value &&
       std::is_convertible<U&&, Ref<Bar>>::value>::type>
    Foo(int a, U&& u) : Foo(a, Ref<Bar>{std::forward<U>(u)}) {}
};

int main() {
  Bar b;
  Foo f(5, &b);
}
