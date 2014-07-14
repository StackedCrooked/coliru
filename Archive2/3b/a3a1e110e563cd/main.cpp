#include <iostream>     // cout
#include <vector>       // vector
#include <sstream>
#include <fstream>
using namespace std;

int main()
{
    ofstream f {"test.bin",ios::binary};
    f << "AAorris";
    f.close();
    ifstream i {"test.bin"};
    std::string in;
    i >> in;
    cout << in;
}