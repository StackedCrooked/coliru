//#include <boost/preprocessor.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>

bool IsRegistered(const char * name)
{
    std::cout << "Check: " << name << std::endl;
    return true;
}


#define CAT_IMPL(a, b) a##b
#define CAT(a, b) CAT_IMPL(a, b)


#define TEST_IMPL(Name) \
    struct Name { \
        Name() { \
            if (IsRegistered(#Name)) { \
                implementation(); \
            } \
        } \
        void implementation(); \
    }; \
    Name CAT(g, Name); \
    void Name::implementation()


#define TEST(Name) \
    TEST_IMPL(CAT(Tester_, Name))


TEST(open)
{
    std::ifstream read("main.cpp");
    std::string s;
    while (read >> s) {
        std::cout << s;
    }
}

TEST(open_create)
{
    std::ofstream create("open_create");
    create << "Created!" << std::endl;
}

TEST(test_malloc)
{
    uint32_t n = 1;
    uint32_t sum = 1;
    do
    {
        malloc(n);
        n *= 2;
        sum += n;
    }
    while (sum < 500 * 1000);
}


int main()
{
}
