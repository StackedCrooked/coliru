#include <cstdio>
#include <cstring>

    
    #define FORMAT_STR( ovr, x, y, ... ) \
    { \
       char buf[100]; memset(buf, 0, 100);\
       using namespace std; \
       snprintf(buf, 99,  __VA_ARGS__); \
       ovr->drawStr( x, y, buf );\
   }

struct A {
    void drawStr(int x, int y, char *buf) {
        puts(buf);
    }
};

int main (int argc, char *argv[])
{
    A obj;
    A *pObj = &obj;
    FORMAT_STR(pObj, 10, 10, "hi")
}