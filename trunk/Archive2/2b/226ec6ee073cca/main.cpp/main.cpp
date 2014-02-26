#include <iostream>
#include <type_traits>

class string {
public:
        template<typename T>
        struct remove_p_cv {
            using type =
                typename std::remove_cv<
                    typename std::remove_pointer<T>::type
                >::type;
        };

        template<typename T,
            typename = typename std::enable_if< std::is_same<typename remove_p_cv<T>::type, char>{} >::type>
        string(const T) { std::cout << "p\n"; }

        template<size_t N>
        string(const char (&) [N]) { std::cout << "arr\n"; }
};


int main() {
        const char* c_str = "foo";
        char c[] = "quux";
        char* p = c;
        
        string foo(c_str);
        string bar("bar");
        string baz(c);
        string goo(p);
}
