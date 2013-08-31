#include <iostream>
#include <vector>
using namespace std;
 
int main ()
{
    std::vector<string> V {"i", "can", "has"};
    for (auto const& s : V)
        cout << s << endl;
}