#include <algorithm>
#include <iostream>
#include <string>
 
int main()
{
    std::cout << "larger of 1 and 9999: " << std::max(1, 9999) << '\n'
              << "larger of 'a', and 'b': " << std::max('a', 'b') << '\n'
              << "longest of \"foo\", \"bar\", and \"hello\": " <<
                  std::max( { "foo", "bar", "hello" },
                            [](const std::string& s1, const std::string& s2) {
                                 return s1.size() < s2.size();
                             }) << '\n';
}