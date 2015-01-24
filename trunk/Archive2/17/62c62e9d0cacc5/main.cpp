#include <unistd.h>
#include <string>
int main()
{
    std::string str="echo aaa | tee -a /tmp.t.log";
    execvp("/bin/bash -c",const_cast<char*>(str.c_str()));
}