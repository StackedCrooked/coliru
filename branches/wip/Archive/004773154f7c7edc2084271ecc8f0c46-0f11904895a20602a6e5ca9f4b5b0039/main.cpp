#include <memory>
#include <cstdlib>

template<typename T, typename Sign>                                 
struct is_functor 
{                                                                   
    typedef char yes[1];                                            
    typedef char no [2];                                            
    template <typename U, U> struct type_check;                     
    template <typename _1> static yes &chk(type_check<Sign, &_1::operator()>*);
    template <typename   > static no  &chk(...);                    
    static bool const value = sizeof(chk<T>(nullptr)) == sizeof(yes);     
};

struct haha_nice_try {
    template <typename T>
    void operator()(T) {}
};

static_assert(is_functor<haha_nice_try, void(haha_nice_try::*)(int)>::value, "");

int main() {}