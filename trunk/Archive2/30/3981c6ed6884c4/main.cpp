#include <string>
#include <iostream>

int Pointer_Function(const char* _output);
int Pointer_to_Pointer_Function(const char** text );

int main() {

    const char* input = "This";
    printf("1. %s \n", input);
    Pointer_Function(input);
    printf("5. %s \n", input);

       int test;
       std::cin >> test;
}

int Pointer_Function(const char* _output) {
       _output = "Datenmanipulation 1";
       printf("2. %s \n", _output);

       Pointer_to_Pointer_Function(&_output);

       printf("4. %s \n", _output);
    return 0;
}

int Pointer_to_Pointer_Function(const char** text ) {

       printf("3. %s \n", *text);
       const char* input = "HalliHallo";

       *text = input;
       printf("3.1. %s \n", *text);
    return 0;
}