// [temp.expl.spec]/6

class String { };
template<class T> class Array { /* ... */ };
template<class T> void sort(Array<T>& v) { /* ... */ }
void f(Array<String>& v) {
  sort(v); // use primary template
           // sort(Array<T>&), T is String
}

template<> void sort<String>(Array<String>& v); // error: specialization
                                                // after use of primary template
template<> void sort<>(Array<char*>& v);        // OK: sort<char*> not yet used
template<class T> struct A {
  enum E : T;
  enum class S : T;
};
template<> enum A<int>::E : int { eint };         // OK
template<> enum class A<int>::S : int { sint };   // OK
template<class T> enum A<T>::E : T { eT };
template<class T> enum class A<T>::S : T { sT };
template<> enum A<char>::E : int { echar };       // ill-formed, A<char>::E was instantiated
                                                  // when A<char> was instantiated
template<> enum class A<char>::S : int { schar }; // OK