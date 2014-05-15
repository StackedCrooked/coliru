#include<iostream>
#include<string>
#include<vector>

int main() {
    std::string array;
    char c = getchar();
    while (c != EOF) {
        if(islower(c) || (c!=' ' && c!='\n'))
            array.push_back(c);
        c = getchar();
    }
    std::cout << array;
}