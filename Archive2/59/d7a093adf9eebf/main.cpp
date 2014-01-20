#include <iostream>
#include <sstream>
#include <limits>
 
int main()
{
    std::istringstream input("1\n"
                             "some 4 non-numeric input\n"
                             "2\n");
    for(;;) {
        int n;
        input >> n;
 
        if (input.eof() || input.bad()) {
            break;
        } else if (input.fail()) {
            input.clear(); // unset failbit
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
        } else {
            std::cout << n << '\n';
        }
    }
}