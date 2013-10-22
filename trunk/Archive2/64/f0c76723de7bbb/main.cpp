#include <vector>
#include <map>
#include <numeric>
#include <iostream>

int main()
{
    using namespace std;

    // map numbers to english names and roman literals
    auto m = map <int, vector <string>> { { 1, { "One",   "I"   } },
                                          { 2, { "Two",   "II"  } },
                                          { 3, { "Three", "III" } },
                                          { 4, { "Four",  "IV"  } } };

    // get vector of answers for number "3"
    auto v = m.at (3);

    // print result
    cout << accumulate (begin (v),
                        end   (v),
                        string { "3: " },
                        [] (string acc, const string& s) { return acc + s + ", "; })
         << std::endl; 
}