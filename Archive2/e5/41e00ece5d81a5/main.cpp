#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

int isPrime(int i)
{
    if (i < 2) {
        return 0;
    } else if (i % 2 == 0 && i != 2) {
        return 0;
    } else {
        for (int j = 3; j <= sqrt(i); j = j + 2) {
            if (i % j == 0) {
                return 0;
            }
        }

        return 1;
    }
}

int toInt(char letter)
{
    if (int(letter) >= 97 && int(letter) <= 122 )
    {
        return int(letter) - 96;
    } else {
        return int(letter) - 38;
    }
}

int main()
{
    std::stringstream cin("abcdefGHaBC");
    
    string line;
    vector<int> results;
    int sum;

    while (getline(cin, line))
    {
        sum = 0;

        for(string::iterator i = line.begin(); i != line.end(); ++i)
        {
            sum += toInt(*i);
        }
        results.push_back(isPrime(sum));
    }

    for (vector<int>::const_iterator i = results.begin(); i != results.end(); ++i)
    {
        if (*i)
        {
            cout << "It is a prime word." << endl;
        } else {
            cout << "It is not a prime word." << endl;
        }
    }
    return 0;
}