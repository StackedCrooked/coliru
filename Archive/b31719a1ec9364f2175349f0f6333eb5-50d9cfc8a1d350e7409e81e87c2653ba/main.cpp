typedef unsigned uint32_t;

uint32_t stringToInt1(char const* buffer, int len) {
    uint32_t result = buffer[0] - '0';
    for (int i = 1; i < len; i++) {
        result *= 10;
        result += buffer[i] - '0';
    }
    return result;
}

uint32_t stringToInt2(char const* buffer, int len) {
    uint32_t result = buffer[0] - '0';
    for (int i = 1; i < len; i++)
        result = result*10 + buffer[i] - '0';
    return result;
}

uint32_t stringToInt3(char const* buffer,int len) {
   uint32_t result = buffer[0] - '0';
   buffer++;
   for (int i=1;i<len;i++) {
       result = (result<<3)+(result<<1)+(*buffer)-'0';
       buffer++;
   }
   return result;
}

uint32_t stringToInt4(char const* buffer, int len) {
    uint32_t result=(buffer++)[0] - '0';    
    while (--len>0) 
        result = result*10+((buffer++)[0]-'0');
    return result;
}
uint32_t stringToInt5(char const* buffer, int len) {
    uint32_t result=buffer[0] - '0';
    buffer++;
    while (--len>0) {
        result = result*10+(buffer[0]-'0');
        ++buffer;
    }
    return result;
}

uint32_t stringToInt6(char const* buffer, int len) {
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
    char const* str;
    int len;
    uint32_t result;
};

typedef uint32_t(*func_type)(char const* buffer, int len);

template<func_type func>
void do_test(const char* name, bool practice) {
    static const test_type data[] =  { //5231134880
        {"725581614", 9, 725581614},
        {"1658", 4, 1658},
        {"7578536", 7, 7578536}, 
        {"216", 3, 216},
        {"21155", 5, 21155},
        {"5", 1, 5},
        {"95260546", 8, 95260546},
        {"237839", 6, 237839},
        {"78", 2, 78},        
        {"1877126498", 10, 1877126498},
    };
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
