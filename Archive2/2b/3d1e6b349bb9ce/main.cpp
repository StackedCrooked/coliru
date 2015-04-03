#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



int main()
{
    string original("tesztelek");
    string test;
    std::copy_if(original.begin(), original.end(), test.begin(), [](const std::string::value_type& currChar) -> bool {
            std::cout << currChar;
      return true;
     });

    return 0;
}
