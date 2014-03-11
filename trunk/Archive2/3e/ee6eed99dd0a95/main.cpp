#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

class string_wrap {
  string data;
public:
  string_wrap(string s) : data(std::move(s)) {}
  string_wrap() = default;
  string_wrap(string_wrap const& s) : data(s.data) { cout << "copy" << endl; }
  string_wrap(string_wrap&& s) : data(std::move(s.data)) { cout << "move" << endl; }
  string& get() noexcept { return data; }
  string const& get() const noexcept { return data; }
};

string_wrap reverse(string_wrap s) {
    std::reverse(begin(s.get()), end(s.get()));
    return s;
}

int main() {
    string_wrap s {{"abcdefg"}};
    
    string_wrap s1 = reverse(s);           //copy
    string_wrap s2 = reverse(std::move(s));//move
// don‘t use s anymore
}