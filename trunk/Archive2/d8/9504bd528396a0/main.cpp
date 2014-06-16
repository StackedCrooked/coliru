#include <iostream>
#include <string>

void fun(const std::string& str1, const std::string& str2, const std::string& str3)
{
    std::cout << str1 << " " <<  str2 << " " <<  str3 << std::endl;
}

void fun2(const std::string& str1, const std::string& str2, const std::string& str3,
          const std::string& str4, const std::string& str5, const std::string& str6)
{
    std::cout << str1 << " " <<  str2 << " " <<  str3
              << " " << str4 << " " <<  str5 << " " <<  str6
              << std::endl;
}

std::string norm(const std::string& str)
{
    return "(" + str + " THIS IS THE NORM!!!" + ")";
}

template <typename F1, typename F2, typename... PTypes>
void double_func(F1 func1, F2 func2, PTypes&... params)
{
    func1(params..., func2(params)...);
}

int main(int /*argc*/, char** /*argv*/)
{
    double_func(fun2, norm, "hello", "there", "!");

    return 0;
}
