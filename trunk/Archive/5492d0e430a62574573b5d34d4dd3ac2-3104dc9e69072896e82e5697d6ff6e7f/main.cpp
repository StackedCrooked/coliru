#include <cstdio>
#include <string>
#include <iostream>

int main () {
    auto num1 = 3.14159265358979323846;
    int result;

    printf("%lA\n", num1);

    std::cout << std::endl;
    std::cout << "Input:" << std::endl;
    std::string input;
    std::cin >> input;
    std::cout << "Got: " << input << std::endl;

    double num2;
    result = sscanf(input.c_str(), "%lA", &num2);
    std::cout << "num2 is " << num2 << " and result is " << result << std::endl;
}