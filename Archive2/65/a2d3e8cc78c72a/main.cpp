#include <cstddef>
#include <iostream>
#include <type_traits> 
#include <utility> 

class string {
public:
    string(const char *) {std::cout << "public const char *\n";}
    
private:
    template<typename T>
    friend string make_string(const T &);
    
    string(const char*, const std::true_type &) {std::cout << "const char *\n";}
    
    template<std::size_t N>
    string(const char(&)[N], const std::false_type &) {std::cout << "const char(&)[" << N << "]\n";}
};

template<typename T>
string make_string(const T &t) {return string(t, std::is_same<const char *, T>());}

int main() {
    const char* c_str = "foo";
    auto foo = make_string(c_str);      // ok will call string(const char*)
    auto bar = make_string("bar");      // ok, will call the array version
    string s("foo");
    string s2(c_str);
}