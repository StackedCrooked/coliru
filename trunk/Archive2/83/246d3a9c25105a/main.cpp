#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    cout<<std::system("ls -l >test.txt");
    return 0;
}