#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

#include <boost/type_traits.hpp>

namespace detail {

    template <class T, bool is_pointer = boost::is_pointer<T>::value>
    struct pointer_traits {
        enum {
            level = 1 + pointer_traits<typename boost::remove_pointer<T>::type>::level
        };
        
        typedef typename pointer_traits<typename boost::remove_pointer<T>::type>::base_type base_type;
    };
    
    template <class T>
    struct pointer_traits<T, false> {
        enum {
            level = 0
        };
        
        typedef T base_type;
    };
    
    
    template <class To, class From, bool deref = (pointer_traits<To>::level < pointer_traits<From>::level), int steps = (pointer_traits<To>::level - pointer_traits<From>::level)>
    struct promote_ptr {
        To operator() (From arg);
    };
    
    template <class To, class From, int steps>
    struct promote_ptr<To, From, true, steps> {
        To operator() (From & arg) {
            return promote_ptr<To, typename boost::remove_pointer<From>::type>()(*arg);
        }
    };
    
    template <class To, class From>
    struct promote_ptr<To, From, false, 1> {
        To operator() (From & arg) {
            return promote_ptr<To, typename boost::add_pointer<From>::type>()(&arg);
        }
    };
    
    template <class To, class From>
    struct promote_ptr<To, From, false, 0> {
        To operator() (From arg) {
            return arg;
        }
    };

}

template <class To, class From>
To promote_ptr(From & f) {
    return detail::promote_ptr<To, From>()(f);
};

int main()
{
    std::cout << typeid(detail::pointer_traits<int *****>::base_type).name() << std::endl;
    std::cout << detail::pointer_traits<int *****>::level << std::endl;
    
    int a = 100;
    int * pa = &a;
    std::cout << "[1]: " << pa << std::endl;
    int ** ppa = &pa;
    std::cout << "[2]: " << ppa << std::endl;
    int *** pppa = &ppa;
    std::cout << "[3]: " << pppa << std::endl;
    int **** ppppa = &pppa;
    std::cout << "[4]: " << ppppa << std::endl;
    
    std::cout << "0: " << promote_ptr<int>(a) << std::endl;
    //std::cout << "1: " << *promote_ptr<int *>(a) << std::endl;
    std::cout << "1: " << promote_ptr<int *>(pppa) << std::endl;
    
}
