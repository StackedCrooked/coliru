#include <string>
#include <vector>

std::string operator"" _s( const char* s, size_t sz ) { return {s, s+sz}; }

template<typename T>
std::vector<std::string> make_vector( std::initializer_list<T> il ) {
    return {il};
}

int main() {
    auto compile = make_vector<std::string>( { "uie","uieui","ueueuieuie" } ); 
    auto compile_too = make_vector<std::string>( { "uie"_s, "uieui", "ueueuieuie" } ); 
    auto do_not_compile = make_vector( { "uie","uieui","ueueuieuie" } ); 
}
