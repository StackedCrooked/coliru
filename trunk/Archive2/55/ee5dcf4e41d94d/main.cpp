#include <string>

namespace Logger {
    std::string resultantOutput = "";
    
    void log(std::string message) {
        resultantOutput += message;
    };
}

// via: https://github.com/philsquared/Catch/blob/35f4266d0022ed039923fbbba2c4495435ad1465/single_include/catch.hpp#L58
#define INTERNAL_UNIQUE_NAME_LINE2( name, line ) name##line
#define INTERNAL_UNIQUE_NAME_LINE( name, line ) INTERNAL_UNIQUE_NAME_LINE2( name, line )
#define INTERNAL_UNIQUE_NAME( name ) INTERNAL_UNIQUE_NAME_LINE( name, __LINE__ )

namespace Logger {
    struct run_registrar {
		template <typename Fun>
		run_registrar(Fun&& registrant) {
			registrant();
		}
	};
}

#define RUNTESTS( ... ) \
	namespace { static ::Logger::run_registrar INTERNAL_UNIQUE_NAME(run_registrar) (__VA_ARGS__); }

#include <iostream>
// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
    std::cout << Logger::resultantOutput << std::endl;

	return 0;
}

RUNTESTS([]{
    Logger::log("Foo");
    Logger::log("Bar");
})