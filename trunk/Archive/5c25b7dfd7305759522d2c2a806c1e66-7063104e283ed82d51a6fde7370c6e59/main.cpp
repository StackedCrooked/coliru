#include <iostream>
#include <vector>
using namespace std;

void bigresol(vector<string> art)
{
    cout << "Increased Resolution of your artwork" << endl;

    for (int i = 0; i < art.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << art[i];
        }
        // unnecessary: cout << endl;
    }
}

int main() {
    bigresol({"abcdef"});
}