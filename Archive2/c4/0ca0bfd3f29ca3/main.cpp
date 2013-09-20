#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

int main ()
{
typedef std::chrono::high_resolution_clock clock;
typedef std::chrono::duration<float, std::nano> ns;
auto t0 = clock::now();
#if VER==1
for (int i = 0; i < 100000; ++i)
{
    std::string l_czTempStr =  std::string{"Test data1"} + "Test data2" + "Test data3";
}
#elif VER==2
for (int i = 0; i < 100000; ++i)
{
    std::string l_czTempStr =  "Test data1"; 
    l_czTempStr += "Test data2";
    l_czTempStr += "Test data3";
}
#elif VER==3
for (int i = 0; i < 100000; ++i)
{
    std::string l_czTempStr =  "Test data1"; 
    l_czTempStr.append("Test data2");
    l_czTempStr.append("Test data3");
}
#elif VER==4
for (int i = 0; i < 100000; ++i)
{
    std::ostringstream oss("Test data1"); 
    oss << "Test data2";
    oss << "Test data3";
    std::string l_czTempStr = oss.str();
}
#endif
auto t1 = clock::now();
std::cout << ns(t1-t0).count() << "ns\n";
}