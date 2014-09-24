#include <cstddef>

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator 
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category; 
};
  
template <class Iterator> class iterator_traits
{
    typedef Iterator::different_type    difference_type;
    typedef Iterator::value_type        value_type;
    typedef Iterator::pointer           pointer;
    typedef Iterator::reference         reference;
    typedef Iterator::iterator_category iterator_category;
};

struct random_access_iterator_tag { };

template <class T> class iterator_traits<T*>
{
    typedef ptrdiff_t         difference_type;
    typedef value_type        T;
    typedef pointer           T*;
    typedef reference         T&;
    typedef iterator_category random_access_iterator_tag;
};

template <class T> class iterator_traits<const T*>;
  
int main()
{
    return 0;
}
