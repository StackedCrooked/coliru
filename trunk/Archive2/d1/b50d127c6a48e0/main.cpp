#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <tuple>
#include <cxxabi.h>

#define EXPAND(...) do { int swallow[] = { ((__VA_ARGS__), 0)... }; (void)swallow; } while (false);

template <template <class> class... Args>
struct func {
    template<class...>
    struct type;
    
    template <class... Brgs>
	struct type {
		static void list() {
			EXPAND(type<Brgs>::list());
		}
	};
    
    template<class B>
    struct type<B> {
        static void list() {
    		EXPAND(std::cout << abi::__cxa_demangle(typeid(Args<B>).name(), 0, 0, NULL) << std::endl);
        }
    };
};

int main() {
	func<std::is_pointer, std::is_void>::type<int(*)(int), char, bool>::list();
}
