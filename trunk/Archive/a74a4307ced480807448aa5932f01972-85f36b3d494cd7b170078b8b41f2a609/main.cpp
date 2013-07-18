#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char** argv) {
    const char* errorString = "Hello world!";
    std::wcout << std::wstring(errorString,errorString+strlen(errorString)).c_str() << std::endl;
    }

