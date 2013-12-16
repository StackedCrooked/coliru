#include <iostream>
#include <sstream>

namespace logger {

    template<typename T> void printParam(std::ostream &os, const T &) {
		os << "?IDX?" << std::endl;
	}

	template<typename... Ts, typename T> void printParam(std::ostream &os, int i, const T &arg0) {
		if(i == 0) {
			os << arg0;
		} else {
			printParam(os, arg0);
		}
	}

	template<typename... Ts, typename T> void printParam(std::ostream &os, int i, const T &arg0, const Ts &... args) {
		if(i == 0) {
			os << arg0;
		} else {
			printParam(os, i - 1, args...);
		}
	}

	template<typename... Ts> void format(std::ostream &os, const char *format, const Ts &... args) {
		while(*format) {
			if(*format == '%') {
				++format;
				if(!*format) {
					break;
				}
				if(*format >= '0' && *format <= '9') {
					printParam(os, *format - '0', args...);
				} else if(*format == '%') {
					os << '%';
				}
			} else {
				os << *format;
			}
			++format;
		}
	}
	
	template<typename... Ts> std::string formatStr(const char *format, const Ts &... args) {
		std::stringstream sstr;
		logger::format(sstr, format, args...);
		return sstr.str();
	}

	template<typename... Ts> void format(const char *format, const Ts &... args) {
		logger::format(std::cout, format, args...);
		std::cout << std::endl;
	}

}

// --8<--8<--8<--

int main() {
    logger::format(std::cerr, "Zomg, %0 + %0 != %1!\n", 1, 3);
}