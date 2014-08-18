#include <iostream>
#include <string>
#include <set>

class StringTracker
{
private:
    std::set<std::string> stringHolder;
public:
     bool seenString(const char* str)
     {
         std::string tempStr;
         tempStr += str;
         if (stringHolder.find(tempStr) == stringHolder.end()) {
             stringHolder.insert(tempStr);
             return false;
         } else {
             return true;
         }
     }       
 };

int main()
{
    StringTracker st;
    std::cout << std::boolalpha;
    std::cout << "Checking for 'foo' - " << st.seenString("foo") << std::endl;
    std::cout << "Checking for 'bar' - " << st.seenString("bar") << std::endl;
    std::cout << "Checking for 'baz' - " << st.seenString("baz") << std::endl;
    std::cout << "Checking for 'foo' again - " << st.seenString("foo") << std::endl;
    return 0;
}
