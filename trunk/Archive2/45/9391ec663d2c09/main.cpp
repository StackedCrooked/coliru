//C++11 code demonstrating call of templated function by specifying
//values of template arguments in runtime. Each argument is taken
//from provided list of types, which is indexed by runtime index.
//
//If function signature depends on template arguments then the best
//way to call it is to wrap the call into function having fixed
//signature.
//
//Be careful: since all combinations of template parameters are
//compiled, your executable can be easily made very large.
//
//Author: https://twitter.com/Soukhinov

#include <cassert>
#include <iostream>
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////
// Dispatcher code:

template<class F, class A, class ...B> struct Dispatch {
    template<class ...C> static inline decltype(&F::template f<C..., A>) f (
		std::size_t const i
	) {
		assert( i <= sizeof...(B) );
		static constexpr decltype(&F::template f<C..., A>) table[] {
			&F::template f<C..., A>, &F::template f<C..., B>...
		};
		return table[i];
	}
};

////////////////////////////////////////////////////////////////////////////
// Usage examples:

//Structure should contain template of static function named «f»
struct Test1 {
	template<class A> static void f(int b) {
		std::cout
			<< typeid(A).name() << ", "
			<< b << std::endl;
	}
};

struct Test2 {
	template<class A, class B> static void f(int c) {
		std::cout
			<< typeid(A).name() << ", "
			<< typeid(B).name() << ", "
			<< c << std::endl;
	}
};

struct Test3 {
	template<class A, class B, class C> static void f(int d) {
		std::cout
			<< typeid(A).name() << ", "
			<< typeid(B).name() << ", "
			<< typeid(C).name() << ", "
			<< d << std::endl;
	}
};

int main(void) {

    //Selecting type number zero from list of types {int, float, double}
    //and calling Test1<int>::f(1). Will print something like «int, 1».
    Dispatch<Test1, int, float, double>::f(0)(1);

    #define LIST int, float, double

    //Calling Test2<int, float>::f(2). Will print «int, float, 2»
	Dispatch<Dispatch<Test2, LIST>, LIST>::f(0)(1)(2);

    //Calling Test3<int, float, double>::f(3). Will print «int, float, double, 3»
	Dispatch<Dispatch<Dispatch<Test3, LIST>, LIST>, LIST>::f(0)(1)(2)(3);

	return 0;
}