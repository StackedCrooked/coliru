struct f {
    
    int arf ( char a, double b ) {
        return 0;
    }
    
};

#include <string>
#include <cxxabi.h>

namespace detail {
    std::string demangle ( const std::type_info& id ) {
		int status;
		char* unmangled = abi::__cxa_demangle(id.name(), 0, 0, &status);
		std::string realname = unmangled;
		free( unmangled );
		return realname;
	}
}

#include <iostream>

int main () {
    std::cout << detail::demangle( typeid( &f::arf ) ) << std::endl;
}