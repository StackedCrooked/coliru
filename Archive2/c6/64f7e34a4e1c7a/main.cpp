#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>

template <typename ElementType>
class WorkingSimpleVector {
 public:
    const ElementType * elements_;
    size_t count_;

    // ...

    template <typename ET = ElementType>
    inline typename std::enable_if<std::is_same<ET, char>::value && std::is_same<ElementType, char>::value, bool>::type
    operator==(const std::string & other) const {
        if (count_ == other.length())
        {
            return memcmp(elements_, other.c_str(), other.length()) == 0;
        }
        return false;
    }
};

template <typename ElementType>
class NotWorkingSimpleVector {
 public:
    const ElementType * elements_;
    size_t count_;

    // ...

    inline typename std::enable_if<std::is_same<ElementType, char>::value, bool>::type
    operator==(const std::string & other) const {
        if (count_ == other.length())
        {
            return memcmp(elements_, other.c_str(), other.length()) == 0;
        }
        return false;
    }
};

int main(int argc, char ** argv) {
    // All of the following declarations are legal.
    WorkingSimpleVector<char> wsv;
    NotWorkingSimpleVector<char> nwsv;
    WorkingSimpleVector<int> wsv2;
    std::string s("abc");
    

    // But this one fails: error: no type named ‘type’ in ‘struct std::enable_if<false, bool>’
    NotWorkingSimpleVector<int> nwsv2;

    //(wsv == s);  // LEGAL (wanted behaviour)
    //(nwsv == s);  // LEGAL (wanted behaviour)
    // (wsv2 == s);  // ILLEGAL (wanted behaviour)
    // (nwsv2 == s);  // ??? (unwanted behaviour)
    
}