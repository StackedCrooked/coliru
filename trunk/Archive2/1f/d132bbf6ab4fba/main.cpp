#include <type_traits>

template <bool B>
using expr = std::integral_constant <bool, B>;

template <bool B>
using _not = expr <!B>;

template <template <typename> class F>
struct neg_f
{ 
    template <typename T>
    using map = _not <true>;
    
    using map1 = int;
};

struct neg2_f
{
    template <typename T>
    using map = _not <true>;
};

template <typename T>
using pred = expr <true>;

template <template <typename> class F>
struct fun {};

struct foo {};

template< template<typename> class F, class T>
T func(const F<T>&);

template <void (*T)(int &)>
void doOperation()
{
  int temp=0;
  T(temp);
  //std::cout << "Result is " << temp << std::endl;
}

template< template<typename> class F>
using neg = typename neg_f<F>::template map;

template< template<typename> class F>
using neg1 = typename neg_f<F>::map1;

template<class T>
using neg2 = typename neg2_f::map<T>;



int main ()
{
    neg_f<pred>::map<foo> tf;
    fun<neg_f<pred>::map> ftf;
    neg<pred> t;
    neg1<pred> t1;
    neg2<foo> t2;
    
    //fun<neg_f<pred>::map<foo> >{};
    //fun<neg<pred> >{};
}
