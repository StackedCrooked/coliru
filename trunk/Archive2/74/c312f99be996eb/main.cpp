#include <iostream>

using namespace std;

int main()
{
    cout << "Is this going to compile?\n";
    
    auto cout = 0;
    std::cout << "what is it? " << (cout << 1);
}
