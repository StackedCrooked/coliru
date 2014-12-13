#include <iostream>
 using namespace std;
int main()
{
    int n = 0x41424344;
    std::cout.write(reinterpret_cast<char*>(&n), sizeof n) << '\n';
 
    char c[]="This is sample text.";
    std::cout.write(c,4)<<'\n';
    cout<<"s"<<endl;
}