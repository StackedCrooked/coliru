#include <iostream>
#include <sstream>

int main () {    
    
    // input stream
    float my_first_float, my_second_float;
    std::istringstream america("-3.121 -4.535");
    america >> my_first_float;
    america >> my_second_float;
    std::cout << "AMERICA, FUCK YEAH:" << '\n'
    << "==================" << '\n'
    << "'MERICA'S my_first_float: " << my_first_float << '\n'
    << "'MERICA'S my_second_float: " << my_second_float << '\n' << '\n';
 
    std::istringstream america_question_mark("-3,121 -4,535");
    america_question_mark >> my_first_float;
    america_question_mark >> my_second_float;
    std::cout << "America... uhm. Yes?" << '\n'
    << "==================" << '\n'
    << "my_first_float: " << my_first_float << '\n'
    << "my_second_float: " << my_second_float << '\n' << '\n';
    std::cout << "A... America...\nu___u\n";
    
}