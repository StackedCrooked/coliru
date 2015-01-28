template <class T> struct Base { Base* p; };
template <class T> struct Derived : public Base<T> { typename Derived::Base* p; };
template<class T, template<class> class U = T::template Base> struct Third {};