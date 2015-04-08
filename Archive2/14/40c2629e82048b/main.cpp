#include <iostream>
#include <string>

#include <boost/signals2.hpp>
#include <boost/lambda/lambda.hpp>

using namespace std;


void f(const char * const str1, const char * const str2);


boost::signals2::signal<void (string, string)> cSignal;


int main(void) {
    string str1("Hello");
    string str2("World");
    
    cSignal.connect(boost::bind(f, _1, _2));
    
    cSignal(str1, str2);
    
    return 0;
}


void f(const char * const str1, const char * const str2) {
    printf("%s, %s\n", str1, str2);
}