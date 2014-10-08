#include <iostream>
#include <stdexcept>
#include <cstdint>

void log(const char *s)
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

template<typename T, typename... Args>
void log(const char *s, T value, Args... args)
{
while (*s) {
    if (*s == '%') {
        if (*(s + 1) == '%') {
            ++s;
        }
        else {
            std::cout << value;
            log(s + 1, args...); // call even when *s == 0 to detect extra arguments
            return;
        }
    }
    std::cout << *s++;
}
throw std::logic_error("extra arguments provided to printf");
}

template<typename X,typename Y,typename Z >
void checkParameter( X val, Y lower, Z upper)
{
    log("checkParameter, val = % , lower= % , upper= %  \n", val,
                          lower,upper );
    if( ( val > upper) || ( val < lower) )
    {
        //ASSERT(false);
    }
}

int main()
{
    int64_t var = 8070450530100445183;
    checkParameter( var, 0LL, 8070450530100445183LL);
}