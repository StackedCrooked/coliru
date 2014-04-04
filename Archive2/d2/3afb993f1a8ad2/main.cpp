#include <sstream>
#include <cstdarg>
#include <cstdio>

void OutputDebugString(const char* p);

struct logit_impl {
    logit_impl(const char* file, int line) {ss<<file<<'('<<line<<"): ";}
    ~logit_impl() {ss<<'\n';OutputDebugString(ss.str().c_str());}
    int operator()(const char* format, ...) {va_list arg; va_start(arg,format);int r=operator()(format, arg);va_end(arg);return r;}
    int operator()(const char* format, va_list arg) {char buf[1024]; int r=vsnprintf(buf, 1024, format, arg); ss.write(buf, (r<1024?r:1024)); return r;}
    template<class T> std::ostream& operator<<(T&& rhs) {return ss<<std::forward<T>(rhs);}
private:
    std::ostringstream ss;
}; 
#define logit logit_impl(__FILE__,__LINE__)





//Testing code
#include <iostream>

void OutputDebugString(const char* p) {std::cout << p;}

int main() {
    logit("HI %s", "Smith");
    logit << "BANANAS " << 2;
}