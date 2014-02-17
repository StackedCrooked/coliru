#include <iostream>
#include <vector>
#include <string>

void some_function()
{
    std::vector<std::string> K{"X","Y","Z"};
    std::vector<std::string> Y{"x","y","z"};
    std::vector<std::string> YYY(3);
    
    for(int R = 0; R < 3; ++R)
    {
        YYY[R] = K[R] + " equals " + Y[R];
    }
    
    for(int R = 0; R < 3; ++R)
    {
        std::cout << YYY[R] << std::endl;
    }
}

int main()
{
    some_function();
}
