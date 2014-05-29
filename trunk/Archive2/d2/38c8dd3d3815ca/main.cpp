#include <cassert>  // assert
#include <iostream> // std::cerr, std::endl
#include <utility>  // std::forward

template <template <class...> class Target, unsigned N, class C,
        class R, class T, class ...Ts>
struct Recurse : Recurse <Target, N - 1, C, R, T, T, Ts...> {
};

template <template <class...> class Target, class C, class R,
        class T, class ...Ts>
struct Recurse<Target, 0, C, R, T, Ts...> {
	typedef Target<C, R, Ts...> type;
};

template <template <class...> class Target, unsigned N, class C,
        class R, class T>
using Type = typename Recurse<Target, N, C, R, T>::type;

template <class C, typename R, typename ...Ts>
using TargetNonConst = R (C::*)(Ts...);

template <class C, typename R, typename ...Ts>
using TargetConst = R (C::*)(Ts...) const;

template <int ...Is>
struct Sequence {
};

/**
 * Used to generate a sequence of integers.
 */
template <int N, int ...Is>
struct GenerateSequence : GenerateSequence<N - 1, N - 1, Is...> {
};

template <int ...Is>
struct GenerateSequence<0, Is...> : Sequence<Is...> {
};

/**
 * Type definition for `R (C::*)(T, ..., T)` where `T` appears `N` times.
 */
template<unsigned N, class C, class R, class T>
using NaryMethodNonConst = Type<TargetNonConst, N, C, R, T>;

/**
 * Type definition for `R (C::*)(T, ..., T) const` where `T` appears `N` times.
 */
template<unsigned N, class C, class R, class T>
using NaryMethodConst = Type<TargetConst, N, C, R, T>;

////////////////////////////////////////////////////////////////////////////////

#define TMP ( std::forward<C>(caller).*method )( array[Indices]... )
template <typename C, typename M, typename T, int ...Indices>
auto unpackAndCall(C &&caller, M method, const T *array,
		Sequence<Indices...>) -> decltype( TMP ) {
	return TMP;
}
#undef TMP

/**
 * Call a method with each element of an array as an argument.
 * @tparam N Number of input arguments.
 * @param caller The object.
 * @param method The function.
 * @param array The array.
 */
#define TMP unpackAndCall( std::forward<C>(caller), method, array, \
		GenerateSequence<N>() )
template <int N, typename C, typename M, typename T>
auto unpackAndCall(C &&caller, M method, const T *array)
		-> decltype( TMP ) {
	return TMP;
}
#undef TMP

////////////////////////////////////////////////////////////////////////////////
// EXAMPLE /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class A {
  
  int sum;

public:

  A() : sum(0) {
  }
  
  // Delete these because they're unimportant for the example
  A(const A &) = delete;
  A &operator=(const A &) = delete;

  template <typename ...Ts>
  void setSum(Ts ...arguments) {
    sum = 0;
    int array[] = {arguments...};
    for(size_t i = 0; i < sizeof...(Ts); i++) {
        sum += array[i];
    }
  }
  
  int getSum() const {
      return sum;
  }
  
};

int main() {
    // A is just a class that keeps track of a variable, sum.
    // sum is initialized to 0 and setSum changes its value
    A a;
    
    // Usually we would call setSum like so...
    a.setSum(1, 2, 3, 4); // Adds up to 10
    assert( a.getSum() == 10 ); // Easy!
    
    ////////////////////////////////////////////////////////////////////////////

    // But hey, what if we have some numbers in an array but we
    // still want to call the variadic function?
    int array[4] {10, 20, 30, 40}; // Adds up to 100
    
    // Pointer to the setSum function
    NaryMethodNonConst<4, A, void, int> pointer = &A::setSum;
    
    // Unpack the array and call the setSum function
    unpackAndCall<4>(a, pointer, array);
    
    assert( a.getSum() == 100 ); // Yay!

    ////////////////////////////////////////////////////////////////////////////

    std::cerr << "Everything worked! " << std::endl;
    
    return 0;
}
