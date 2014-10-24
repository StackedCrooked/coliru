#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <boost/regex.hpp>

void func0(std::string s)
{
    auto pat = boost::regex{R"(([_[:alnum:]]+)@([UAMI]))"};
    auto match = boost::smatch{};
    
    if (!boost::regex_match(s, match, pat))
    {
        assert(false);
        return;
    }
    auto name = match[1];
    auto type = match[2];
    (void)name;
    (void)type;
}

void func1(std::string s)
{
    auto pat = std::regex{R"(([_[:alnum:]]+)@([UAMI]))"};
    auto match = std::smatch{};
    
    if (!std::regex_match(s, match, pat))
    {
        assert(false);
        return;
    }
    auto name = match[1];
    auto type = match[2];
    (void)name;
    (void)type;
}

void func2(std::string s)
{
    auto pos = s.find('@');
    if (std::string::npos == pos)
    {
        assert(false);
        return;
    }
    auto type = std::string(s, pos + 1);
    auto name = std::string(s, 0, pos);
    (void)name;
    (void)type;
}

void func3(std::string s)
{
    auto pat = std::regex{R"((.+)@([UAMI]))"};
    auto match = std::smatch{};
    
    if (!std::regex_match(s, match, pat))
    {
        assert(false);
        return;
    }
    auto name = match[1];
    auto type = match[2];
    (void)name;
    (void)type;
}

int main()
{
    
    {
        auto begin = std::chrono::system_clock::now();
        for (auto i = 0; i < 10000; ++i)
            func0("test_1_ch12345@U");
        auto end = std::chrono::system_clock::now();
        std::cout << "func0: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
        
    }
    {
        auto begin = std::chrono::system_clock::now();
        for (auto i = 0; i < 10000; ++i)
            func1("test_1_ch12345@U");
        auto end = std::chrono::system_clock::now();
        std::cout << "func1: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
        
    }
    {
        auto begin = std::chrono::system_clock::now();
        for (auto i = 0; i < 10000; ++i)
            func2("test_1_ch12345@U");
        auto end = std::chrono::system_clock::now();
        std::cout << "func2: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
        
    }
    {
        auto begin = std::chrono::system_clock::now();
        for (auto i = 0; i < 10000; ++i)
            func3("test_1_ch12345@U");
        auto end = std::chrono::system_clock::now();
        std::cout << "func3: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
        
    }
}
