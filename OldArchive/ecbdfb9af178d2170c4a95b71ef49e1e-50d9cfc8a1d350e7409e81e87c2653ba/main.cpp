typedef unsigned uint32_t;

uint32_t stringToInt1(unsigned char const* buffer, unsigned len) {
    uint32_t result = buffer[0] - '0';
    for (unsigned i = 1; i < len; i++) {
        result *= 10;
        result += buffer[i] - '0';
    }
    return result;
}

uint32_t stringToInt2(unsigned char const* buffer, unsigned len) {
    uint32_t result = buffer[0] - '0';
    for (unsigned i = 1; i < len; i++)
        result = result*10 + buffer[i] - '0';
    return result;
}

uint32_t stringToInt3(unsigned char const* buffer,unsigned len) {
   uint32_t result = buffer[0] - '0';
   buffer++;
   for (unsigned i=1;i<len;i++) {
       result = (result<<3)+(result<<1)+(*buffer)-'0';
       buffer++;
   }
   return result;
}

uint32_t stringToInt4(unsigned char const* buffer, unsigned len) {
    uint32_t result=(buffer++)[0] - '0';    
    while (--len>0) 
        result = result*10+((buffer++)[0]-'0');
    return result;
}
uint32_t stringToInt5(unsigned char const* buffer, unsigned len) {
    uint32_t result=buffer[0] - '0';
    buffer++;
    while (--len>0) {
        result = result*10+(buffer[0]-'0');
        ++buffer;
    }
    return result;
}

uint32_t stringToInt6(unsigned char const* buffer, unsigned len) {
    uint32_t result=(buffer++)[0] - '0';
    --len;
    while (len>=4) {
        result = result*10000+(buffer[0]-'0')*1000+(buffer[1]-'0')*100+(buffer[2]-'0')*10+(buffer[3]-'0');
        buffer += 4;
        len -= 4;
    }
    while (len-->0) 
        result = result*10+((buffer++)[0]-'0');
    return result;
}

#include <ctime>
#include <iostream>
#include <cassert>
#include <iomanip>

struct test_type {
    unsigned char const* str;
    unsigned len;
    uint32_t result;
};

typedef uint32_t(*func_type)(unsigned char const* buffer, unsigned len);
static unsigned const char first[] = "725581614";
static unsigned const char second[] = "1658";
static unsigned const char third[] = "7578536";
static unsigned const char fourth[] = "216";
static unsigned const char fifth[] = "21155";
static unsigned const char sixth[] = "5";
static unsigned const char seventh[] = "95260546";
static unsigned const char eighth[] = "237839";
static unsigned const char ninth[] = "78";
static unsigned const char tenth[] = "1877126498";
static const test_type data[] =  {
    {first, 9, 725581614},
    {second, 4, 1658},
    {third, 7, 7578536}, 
    {fourth, 3, 216},
    {fifth, 5, 21155},
    {sixth, 1, 5},
    {seventh, 8, 95260546},
    {eighth, 6, 237839},
    {ninth, 2, 78},        
    {tenth, 10, 1877126498},
};

template<func_type func>
void do_test(const char* name, bool practice) {
    clock_t begin = clock();
    const int max = practice?100:20000000;
    for(int i=0; i<max; ++i) {
        for(int j=0; j<10; ++j) {
            uint32_t result = func(data[j].str, data[j].len);
            if (result!=data[j].result) {
                std::cerr << name << " converted " << data[j].str << ", " << data[j].len << " into " << result << " instead of " << data[j].result << '\n';
                throw std::exception();
            }
        }
    }
    if (!practice)
    std::cout << name << " did " << max << " conversions in " << (double(clock()-begin)/CLOCKS_PER_SEC) << " seconds.\n";
}

int main() {
    std::cout << "Average measured devation: 0.0247 seconds\nMaximum measured deviation: 0.1145 seconds\n";
    do_test<stringToInt1>("stringToInt1", true);
    do_test<stringToInt1>("stringToInt1", false);
    do_test<stringToInt2>("stringToInt2", true);
    do_test<stringToInt2>("stringToInt2", false);
    do_test<stringToInt3>("stringToInt3", true);
    do_test<stringToInt3>("stringToInt3", false);
    do_test<stringToInt4>("stringToInt4", true);
    do_test<stringToInt4>("stringToInt4", false);
    do_test<stringToInt5>("stringToInt5", true);
    do_test<stringToInt5>("stringToInt5", false);
    do_test<stringToInt6>("stringToInt6", true);
    do_test<stringToInt6>("stringToInt6", false);
}
