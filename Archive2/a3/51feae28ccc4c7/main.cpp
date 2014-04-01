#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>

std::string stringify(int x) { return std::to_string(x); }
std::string stringify(unsigned long long x) { return std::to_string(x); }
std::string stringify(std::nullptr_t) { return "nullptr"; }
template <typename T> std::string stringify(T * ptr) { char buf[32]; snprintf(buf, sizeof buf, "%p", ptr); return buf; }

template <typename T1, typename T2>
void assert_ne(const T1 & a, const T2 & b, const char * ea, const char * eb, const char * file, int line) {
    using T = typename std::common_type<T1, T2>::type;
    if (static_cast<T>(a) == static_cast<T>(b)) {
        std::cout << "assertion failed at " << file << ":" << line << ": " << ea << " (" << stringify(a) << ") == " << eb << " (" << stringify(b) << ")\n";
        std::abort();
    }
}

template <typename T1, typename T2>
void assert_eq(const T1 & a, const T2 & b, const char * ea, const char * eb, const char * file, int line) {
    using T = typename std::common_type<T1, T2>::type;
    if (static_cast<T>(a) != static_cast<T>(b)) {
        std::cout << "assertion failed at " << file << ":" << line << ": " << ea << " (" << stringify(a) << ") != " << eb << " (" << stringify(b) << ")\n";
    	std::abort();
    }
}

#define ASSERT_EQ(a, b) assert_eq(a, b, #a, #b, __FILE__, __LINE__)
#define ASSERT_NE(a, b) assert_ne(a, b, #a, #b, __FILE__, __LINE__)

int main() {
	int x = 42;
	unsigned long long y = 123;
    assert(x == 42);
    assert(y == 123);
	ASSERT_EQ(x, 42);
	ASSERT_EQ(y, 123);
    int * p = nullptr;
    ASSERT_EQ(p, nullptr);
    ASSERT_EQ(nullptr, p);
    int * q = &x;
    ASSERT_EQ(q, q);
    ASSERT_NE(p, q);
    ASSERT_NE(q, p);
    ASSERT_NE(q, nullptr);
    ASSERT_NE(nullptr, q);
    
    // kaboom
    ASSERT_EQ(p, q);
}