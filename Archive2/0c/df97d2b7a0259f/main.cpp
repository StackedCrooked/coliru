#include <stdexcept>
#include <system_error>
#include <string>
#include <iostream>

#include <cstring> // strerror

#include <fstream>

#if defined(_LIBCPP_VERSION) && (_LIBCPP_VERSION >= 1000)
#define HAS_IOS_BASE_FAILURE_DERIVED_FROM_SYSTEM_ERROR 1
#else
#define HAS_IOS_BASE_FAILURE_DERIVED_FROM_SYSTEM_ERROR 0
#endif

using std::cerr;
using std::cout;
using std::endl;


int main(/*int argc, char** argv*/) {
    int rv = EXIT_SUCCESS;
    errno = 0;
    
    try {
        std::ifstream ifs;
        ifs.exceptions(std::ios::badbit | std::ios::failbit);
        ifs.open("DOESN'T EXIST");

    } catch (const std::ios_base::failure& e) {
        
#if (HAS_IOS_BASE_FAILURE_DERIVED_FROM_SYSTEM_ERROR)
        //
        // e.code() is only available if the lib actually follows iso §27.5.3.1.1
        // and derives ios_base::failure from system_error
        // like e.g. libc++
        // http://llvm.org/viewvc/llvm-project/libcxx/trunk/include/ios?revision=193085&view=markup
        // (line 415)
        //
        // and not keeps on deriving it directly from runtime_error
        // like libstdc++
        // https://github.com/mirrors/gcc/blob/master/libstdc%2B%2B-v3/include/bits/ios_base.h#L209
        //
        cout << "libc++ error #"    << e.code().value()  
                << ' '              << e.code().message()
                << ',' << endl << "    ";
#endif
        cout << "libc error #"      << (rv = errno)
                << ": "             << ::strerror(errno)
                << endl;

        cout << e.what() << endl;
        cout << "handled" << endl;
    } 
    
    return rv;
}