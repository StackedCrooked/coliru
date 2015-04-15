#include <vector>
#include <iostream>

template <class T>
struct is_pointer {
    enum { value = false };
};

template <class T>
struct is_pointer<T*> {
    enum { value = true };
};

template<class required1_type, class required2_type, class optional1_ptr_type, class optional2_ptr_type>
void foo(required1_type &a, required2_type& b, optional1_ptr_type o1, optional2_ptr_type o2)
{
  if (!is_pointer<optional1_ptr_type>::value) std::cout << "null passed\n";
  else std::cout << "null not passed\n";
}

int main()
{
    typedef std::vector<double> mytype;
    mytype a, b, c, d;
    foo(a, b, &c, &c);
    foo(a, b, NULL, &c);
}