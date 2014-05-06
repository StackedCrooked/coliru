#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <regex>

#include <random>
#include <functional>
#include <chrono>

#include <thread>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


class FatClass {
    public:
    FatClass()
    {
        std::cout << "NORMAL constructor" << std::endl;
    }

    FatClass(const FatClass& obj)
    {
        std::cout << "COPY constructor" << std::endl;
    }
    
    FatClass(const FatClass&& obj)
    {
        std::cout << "MOVE constructor" << std::endl;
    }
    
    FatClass& operator=(const FatClass& rhs)
    {
        return *this;
    }
    
    FatClass& operator=(FatClass&& rhs)
    {
        return *this;
    }
};

FatClass CreateFatClass() {
    return FatClass();
    
}

int operator "" _bin(const char* literal_string)
{
    std::cout << "operator" << std::endl;
    
    int result = 0;
    int i = 0;
    const char * c = NULL;
    int len = sizeof(literal_string)/sizeof(const char);
    
    for (c = literal_string + len - 1; len>0; c--, len--) {
        if(*c == '1')
        {
            result += pow(2.0, i);
        }
        ++i;
    }
    
    std::cout << "result=" << result << std::endl;
    
    return 123;
}

class Randomizer {
    private:
    
    mt19937 engine;
    
    
    public:
    
    Randomizer()
    {
        engine.seed((unsigned int) chrono::system_clock::now().time_since_epoch().count());
    }
    
    int operator() (int min, int max)
    {
        uniform_int_distribution<int> distribution( min, max );
        return distribution(engine);
    }
};

int main()
{   
    Randomizer rand;
    for(int i=0; i<3; ++i)
        std::cout << rand(1, 100) << std::endl;
    
    
    //regex r("^(0?asd)\\:([0-5][0-9])$", regex::extended);
    
    //if(regex_match("23:59", r, regex::extended))
     //   std::cout << "Datetime MATCH" << std::endl;
    //else
    //    std::cout << "Datetime NOT MATCH" << std::endl;

    
    
    auto fun = [](const string& str){return "LAMBDA: " + str;};
    std::cout << fun("asdadssda") << std::endl;

    int a = 01100011_bin;
    
    auto fun2 = [&](const int i){return "LAMBDA 2: "; a++;};
    std::cout << fun2(a) << std::endl;

    
    
    std::vector<FatClass> vec;
    for(int i=0; i<10; ++i)
        vec.push_back(FatClass());
    
    FatClass f1;
    f1 = CreateFatClass();
    
    FatClass f2;
    f2 = f1;
    
    std::cout << "asdadssda" << std::endl;
    
    
    
    
    return 0;
}



