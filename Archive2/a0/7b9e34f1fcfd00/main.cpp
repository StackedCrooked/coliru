#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>

//Exercises from workshop:
//
//1. Write a code which will be able to transform vector of int to vector of strings.
//Hint: integer type can be converted to string by std::to_string() function.
//
//2. Wirte a code which will change string "example" to uppercase (use std::for_each and std::toupper).
//
//3. Write a code which will count even values from vector of ints std::vector<int> v = {1, 5, 16, 2, 7, 1044, 236, 19, 99};
//
//4. Write a code which will get minimum and maximum value from vector std::vector<int> v = {1, 5, 16, 2, 7, 1044, 236, 19, 99};
//
//5. Write a code which will remove all of odd values from vector std::vector<int> v = {1, 5, 16, 2, 7, 1044, 236, 19, 99};
//
//6. Write a function that will sort a vector of complex numbers based on its magnitude.
//   (Note: magnitude = sqrt(real^2 + imag^2) )
//
//    struct Complex {
//        double real;
//        double imag;
//    };
//
//    sortComplex(std::vector<Complex>& complexNumbers);
//
//    Ex: { {8,15}, {3,4}, {5,12} } -> { {3,4}, {5,12}, {8,15} }
    
int main()
{
    //1.
    std::vector<int> iv = { 10, 9 };
    std::vector<std::string> sv;
    sv.resize(iv.size(), "");
    std::transform(iv.begin(), iv.end(), sv.begin(), [](int i) { return std::to_string(i); });
    for (auto s : sv)
    {
        std::cout << s << std::endl;
    }
    
    //2.
    std::string str = "example";
    std::locale loc;
    //std::for_each(str.begin(), str.end(), [locale](char c) { std::toupper(c, locale) });
}
