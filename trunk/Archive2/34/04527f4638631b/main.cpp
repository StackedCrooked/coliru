#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <tuple>
#include <cxxabi.h>

template <template <class> class... Args>
struct func {
    template<class...>
    struct type;
    
    template <class... Brgs>
	struct type {
		static void list() {
			int swallow[] = { (type<Brgs>::list(), 0)... };
            (void)swallow;
		}
	};
    
    template<class B>
    struct type<B> {
        static void list() {
    		int swallow[] = { ((std::cout << abi::__cxa_demangle(typeid(Args<B>).name(), 0, 0, NULL) << std::endl), 0)... };
            (void)swallow;
        }
    };
};

int main() {
	func<std::is_pointer, std::is_void>::type<int(*)(int), char, bool>::list();
}
