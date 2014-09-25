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
    		char const* type_names[] = { abi::__cxa_demangle(typeid(Args<B>).name(), 0, 0, NULL)... };
    		for (size_t i = 0; i < sizeof...(Args); i++) {
				std::cout << type_names[i] << std::endl;
    		}
        }
    };
};

int main() {
	func<std::is_pointer, std::is_void>::type<int(*)(int), char, bool>::list();
}
