#include <iostream>
#include <cstring> // :/

char* make_char(const char* str, size_t allocation) {
    
    char* result = new char[allocation + 1];
    for(unsigned i = 0; str[i]; ++i)  {
        result[i] = str[i];
    }
    result[allocation] = '\0';
    return result;
}

char* no_allocation_param(const char* str) {
    size_t len = std::strlen(str);
    char* result = new char[len + 1];
    for(unsigned i = 0; i < len; ++i) {
        result[i] = str[i];
    }
    result[len] = '\0';
    return result;
}

int main() {
    char* stuff = make_char("Hello World!", 100);
    char* otherstuff = no_allocation_param("Whoa there");
    std::cout << stuff << '\n' << otherstuff;
    delete[] otherstuff;
    delete[] stuff;
}