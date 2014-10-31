#include <string>

using std::string;

class B {
public:

    string operator ++ () { return "hello"; }
    string operator + () {  return "hello2"; }
};

int main ()
{
    B b;
    string s = +b ;
    s = b+ ; // compile error syntax error : ';'    

    s = b++; 
    s = ++b;

    return 0;
}
