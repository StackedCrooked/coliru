#include <iostream>
#include <cctype>
#include <algorithm>
 

using namespace std;


bool my_isalpha(char c) {
    return 0 != isalpha(c);
}

int main()
{
    string checkcode = "tes22";
    bool all_alpha;
    all_alpha = std::all_of(checkcode.begin(), checkcode.end(), my_isalpha);
    
    cout << all_alpha;
}










