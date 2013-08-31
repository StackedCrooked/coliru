#include <iostream>
#include <string>
#include <vector>


#include <iostream>
#include <cstring>


using namespace std;

class LoggerStream
{
    public:
    LoggerStream() {pos=buf; }
    ~LoggerStream() {cout<<buf<<endl; }
    LoggerStream & operator<<(const char *var) {int len=strlen(var); strcpy(pos,var); pos+=len; return *this;};
    static char buf[1000];
    char *pos;
    
};

char LoggerStream::buf[1000];

    bool flag=true;

#define LOG(x) if (flag) LoggerStream()<<x; else do {} while (false)

const char *func() { LOG("MADAFAKA"); return "kuku";}

int main()
{
    LOG("bla"<<"blee"<<func()<<"cherbaps");
    flag=false;
    LOG("bla"<<"blee");
    flag=true;
    if (true)
        LOG("true");
    else
        LOG("false");
    return 0;
}
