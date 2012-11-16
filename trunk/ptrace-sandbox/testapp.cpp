#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>


#define ENABLE_EVIL_TESTS 1


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
    return ENABLE_EVIL_TESTS || name.find("Evil") == std::string::npos;
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


int main()
{
}
