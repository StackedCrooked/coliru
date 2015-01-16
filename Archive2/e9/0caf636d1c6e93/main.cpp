#include <fstream>
#include <iostream>
#include <string>
 
int main()
{
    int cnt = 0;
    std::ifstream file;
    char buf[10241];
 
    file.rdbuf()->pubsetbuf(buf, sizeof buf);
 
    file.open("/proc/cpuinfo");
 
    for (std::string line; getline(file, line);) {
        cnt++;
    }
 
    std::cout << cnt << '\n';
}