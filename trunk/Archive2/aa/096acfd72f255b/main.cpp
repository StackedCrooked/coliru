#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

std::vector<std::string> myfun() {
    std::vector<std::string> v_of_s;
    v_of_s.push_back("hello");
    v_of_s.push_back("vector");
    v_of_s.push_back("of");
    v_of_s.push_back("strings");
    return v_of_s;
}

int main() {
    using namespace std;

    vector<string> v_of_s = myfun();
    copy(v_of_s.begin(), v_of_s.end(), ostream_iterator<string>(cout, ", "));
    cout << endl;
}