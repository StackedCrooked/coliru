#include <iostream>
#include <stdexcept>

void streamPrintf(const char *s);
template<typename T, typename... Args>
void streamPrintf(const char *s, T value, Args... args)
{
    while (*s)
	{
	    if (*s == '%') {
		  if (*(s + 1) == '%') {
			++s;
		  }
		  else {
			std::cout << value;
			streamPrintf(s + 1, args...);
			return;
		  }
	    }
	    std::cout << *s++;
	}
	throw std::logic_error("extra arguments provided to printf");
}

void streamPrintf(const char *s)
{
while (*s) {
    if (*s == '%') {
        if (*(s + 1) == '%') {
            ++s;
        }
        else {
            throw std::runtime_error("invalid format string: missing arguments");
        }
    }
    std::cout << *s++;
    }
}

int main()
{
	streamPrintf("% %% % %", std::string("Lol"), 6846, std::string("lol"));
}
