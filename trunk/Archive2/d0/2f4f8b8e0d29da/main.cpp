#include <algorithm>
#include <iostream>
#include <string>
 
int main()
{
    std::cout << "smaller of 1 and 9999: " << std::min(1, 9999) << '\n'
              << "smaller of 'a', and 'b': " << std::min('a', 'b') << '\n'
              << "shortest of \"foo\", \"bar\", and \"hello\": " <<
                  std::min( { "foo", "bar", "hello" },
                            [](const std::string& s1, const std::string& s2) {
                                 return s1.size() < s2.size();
                             }) << '\n';
}