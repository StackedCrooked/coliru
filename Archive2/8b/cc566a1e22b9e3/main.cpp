#include <string>
#include <iostream>
 
int main()
{
    std::string a = "http://r3.sinaimg.cn/10230/2015/0228/7b/6/88511732/auto.jpg";
    a.replace(a.rfind("auto"), 4, "3000*3000*3000", 10000); 
    std::cout << a << '\n';
}