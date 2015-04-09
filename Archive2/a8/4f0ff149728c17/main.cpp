#include <string>

#ifndef Logger_h
#define Logger_h

namespace Logger {
    std::string resultantOutput = "";
    
    void log(std::string message) {
        resultantOutput += message;
    };
}

// Just a simple way to get a unique name after passing in a name.
// Concats that name with the line number
//
// via: https://github.com/philsquared/Catch/blob/35f4266d0022ed039923fbbba2c4495435ad1465/single_include/catch.hpp#L58
#define INTERNAL_UNIQUE_NAME_LINE2(name, line) name ## line
#define INTERNAL_UNIQUE_NAME_LINE(name, line) INTERNAL_UNIQUE_NAME_LINE2( name, line )
#define INTERNAL_UNIQUE_NAME(name) INTERNAL_UNIQUE_NAME_LINE(name, __LINE__)

namespace Logger {
    struct runtests_macro_registrar_type {
		template <typename Func>
		runtests_macro_registrar_type(Func&& registrant) {
			registrant();
		}
	};
}

// Defines and Constructs an object of `Logger::runtests_macro_registrar_type` type. This means the constructor is exectuted with __VA_ARGS__ passed in.
// `INTERNAL_UNIQUE_NAME(run_registrar)` could be any name but this allows for easy uniqueness with it still being somewhat named
// The double colon tells the compiler to look in the global scope for that type. This is just in case someone defines somethingof the same name where this is called
//
// via: https://github.com/rmartinho/nonius/blob/01115c1d4062de88ffca798545ac7c70b4ad4623/include/nonius/benchmark.h%2B%2B#L96
#define LOG( ... ) \
	namespace { static ::Logger::runtests_macro_registrar_type INTERNAL_UNIQUE_NAME(runtests_macro_registrar)(__VA_ARGS__); }


// This is just a runner built into this Logger library
#include <iostream>
// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
    std::cout << Logger::resultantOutput << std::endl;

	return 0;
}

#endif



LOG([]{
    Logger::log("Foo");
    Logger::log("Bar");
});

