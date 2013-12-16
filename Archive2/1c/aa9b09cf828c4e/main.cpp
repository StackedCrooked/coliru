#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

int main()
{
    auto l = [x=10]{
        cout << x << endl;
    };
}

