template<class> struct some_trait;       // primary template

template <class T>
struct A : some_trait<T> {               // (1)
  typename some_trait<T>::C a;
};

template<> struct some_trait<struct B> { // (2)
  class C { };
};

struct B : A<B> {                        // (3)
  C b;
};

int
main (int argc, char *argv[])
{
  B a; // legal
}