#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> myfun() {
    return {"hello", "vector", "of", "strings"};
}

int main() {
    using namespace std;

    auto v_of_s = myfun();
    for (auto &s : v_of_s) {
        cout << s << ' ';
    }
    cout << endl;
}