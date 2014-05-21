#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
T &tempRef(T&&t) {
    return t;
}

int main()
{
    string s="And I feel fine ...";
    vector<string> tokens{istream_iterator<string>(tempRef(istringstream(s))),{}};
    for(auto& elem: tokens)
        cout << elem << endl;
}