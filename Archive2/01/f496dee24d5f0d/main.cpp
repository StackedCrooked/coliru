#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

struct true_type {
  enum { value = true };
};

struct false_type {
  enum { value = false };
};

template <bool, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  typedef T type;
};

template<class T>
struct is_pointer : false_type {};

template<class T>
struct is_pointer<T*> : true_type {};


// Ugh!! 
template<>
struct is_pointer<typeof(NULL)> : true_type {};


template<class opt_type_ptr>
typename enable_if<is_pointer<opt_type_ptr>::value, void>::type  
foo(opt_type_ptr o1)
{
    std::cout << "foo" << std::endl;
}

int main()
{
    typedef std::vector<double> mytype;
    mytype a;
    foo(&a);
    foo(NULL);
    // foo(a); fails to compile
    return 0;
}