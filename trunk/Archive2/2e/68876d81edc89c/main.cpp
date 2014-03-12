template <class T>
class A {
public:
  template< template<class> class U >
  void f( int i ) {
    // ...
  }
};


template< class T, template<class> class U >
class B {
public:
  void f( int i ) {
    A<T> a;
    a.template f<U>( i );
  }
};


int main() {
  return 0;
}