#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>


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

#define EVIL_TEST(Name) \
    TEST_IMPL(CAT(Evil_, Name))

#define GOOD_TEST(Name) \
    TEST_IMPL(CAT(Good_, Name))


bool IsRegistered(std::string name)
{
    return name.find("Evil") == std::string::npos;
}


GOOD_TEST(open)
{
    std::ifstream read("main.cpp");
    std::string s;
    read >> s;
    std::cout << s.size() << std::endl;
}


EVIL_TEST(open_create)
{
    std::ofstream create("open_create");
    create << "Created!" << std::endl;
}


GOOD_TEST(test_malloc)
{
    uint32_t n = 1;
    uint32_t sum = 1;
    do
    {
        malloc(n);
        n *= 2;
        sum += n;
    }
    while (sum < 10 * 1000 * 1000);
}


int main()
{
}
