#include <iostream>
#include <vector>
#include <string>
#include <thread>

void myFunc1(char* sz)
{
    std::printf("%s : %s\n", __PRETTY_FUNCTION__ , sz);
}

void myFunc2(char const * const sz)
{
    std::printf("%s : %s\n", __PRETTY_FUNCTION__ , sz);
}

void myFunc3(const std::string& str)
{
    std::printf("%s : %s\n", __PRETTY_FUNCTION__ , str.c_str());
}

int main()
{
    std::string str[5];
    char sz[5][16];

    // startup threads, placing each in our thread vector
    std::vector<std::thread> thrds;
    for(auto i = 0; i < 5; ++i)
    {
        sprintf(sz[i], "%2d", i+1);
        str[i] = sz[i];
        
        thrds.emplace_back(myFunc1, sz[i]);
        thrds.emplace_back(myFunc2, str[i].c_str());
        thrds.emplace_back(myFunc3, std::ref(str[i]));
    }
    
    // wait for all threads to terminate
    for (auto&& t : thrds)
        t.join();
    
    return 0;
}

