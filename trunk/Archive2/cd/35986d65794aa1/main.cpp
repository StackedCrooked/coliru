#include <string>
#include <iostream>
#include <cstdio>

std::string exec_cmd(char const* cmd)
{
    std::string result, file;
    FILE* pipe {popen(cmd, "r")};
    char buffer[256];

    while(fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        file = buffer;
        result += file.substr(0, file.size() - 1);
    }

    pclose(pipe);
    return result;
}

int main()
{
    std::cout << exec_cmd("uname -a") << '\n';
}