#include <iostream>
#include <string>
#include <vector>


#include <iostream>
#include <cstring>


using namespace std;

class LoggerStream
{
    public:
    LoggerStream() {isEnabled=!bufIsInUse; bufIsInUse=true; pos=buf; }
    ~LoggerStream() {cout<<buf<<endl; bufIsInUse=false;}
    LoggerStream & operator<<(const char *var) {if (!isEnabled) return *this; int len=strlen(var); strcpy(pos,var); pos+=len; return *this;};
    static char buf[1000];
    static bool bufIsInUse;
    bool isEnabled;

    char *pos;
    
};

char LoggerStream::buf[1000];
bool LoggerStream::bufIsInUse=false;

    bool flag=true;

#define LOG if (!flag)  do {} while (false); else LoggerStream()

const char *func() { LOG<<"MADAFAKA"; return "kuku";}

int main()
{
    LOG<<"bla"<<"blee"<<func()<<"cherbaps";
    flag=false;
    LOG<<"bla"<<"blee";
    flag=true;
    if (true)
        LOG<<"true";
    else
        LOG<<"false";
    
    LoggerStream LS;
    LS<<"shit";
    LS<<func();
    LS<<"crap";
    return 0;
}
