#include <iostream>
#include <string>

template<typename String>
inline size_t nth_finder(const String& str, const String& find, int nth) {
    size_t pos = 0;
    int start = 0;
    if(nth >= 0) {
        pos = str.find(find);
        while(start != nth && pos != String::npos) {
            pos = str.find(find, pos + find.length());
            ++start;
        }
    }
    else {
        pos = str.rfind(find);
        nth = -nth;
        while(start != nth && pos != String::npos) {
            pos = str.rfind(find, pos - find.length());
            ++start;
        }
    }
    return pos;
}

int main() {
    std::cout << nth_finder(std::string("Hello Hello Hello Hello"), std::string("Hello"), -1);
}