#include <vector>
#include <string>
#include <iostream>

int main()
{
    using namespace std;
    
    vector<string> words = { "Stack", "Overflow" };
    struct { decltype(words) w; } l{words};
    cout << l.w[0];
}