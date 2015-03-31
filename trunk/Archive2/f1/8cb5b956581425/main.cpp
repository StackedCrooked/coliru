#include <string>

template<class T> bool function(std::string *text, T number, T (*f)(std::string, bool));

double doubleFromString(std::string, bool);

int main() {
    std::string text;
    double num = 0.45;
    double (*fn)(std::string, bool) = &doubleFromString;
    function(&text, num, fn);
}