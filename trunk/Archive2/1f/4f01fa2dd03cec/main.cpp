#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

const char* C_TEXT = "Constant text ";
const size_t MAXWIDTH = 10;

void print_foo(const std::string& var_text, int num)
{
    std::cout << C_TEXT
              // align output to left, fill goes to right
              << std::left << std::setw(MAXWIDTH) << std::setfill('.')
              << var_text << ": " << num << '\n';

    std::cout << std::endl;
}


void print_bar(const std::string& var_text, int num)
{
    std::ostringstream ostr; 
    ostr << C_TEXT
          // align output to left, fill goes to right
          << std::left << std::setw(MAXWIDTH) << std::setfill('.')
          << var_text << ": " << num << '\n';

	std::cout << ostr.str() << std::endl;
}

int main()
{
    print_foo("Qwerty", 10);
	print_bar("Qwerty", 10);
}