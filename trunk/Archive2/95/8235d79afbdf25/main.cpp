#include <iostream>
#include <vector>

int main()
{
    int spongebob = 1;
    int squarepants = 2;
    int * patrick = &spongebob;
    int * star = &squarepants;
    std::vector<int *> {patrick, star};
}