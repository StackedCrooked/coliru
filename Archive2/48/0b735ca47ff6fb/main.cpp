#include <algorithm>
using std::min;

#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;
 
int main()
{
    std::cout << "smaller of 1 and 9999: " << std::min(1, 9999) << '\n'
              << "smaller of 'a', and 'b': " << std::min('a', 'b') << '\n'
              << "shortest of \"foo\", \"bar\", and \"hello\": " <<
                  std::min( { "foo", "bar", "hello" },
                            [](const std::string& s1, const std::string& s2) {
                                 return s1.size() < s2.size();
                             }) << '\n';
     cout << "\n\n-------\n\n";
     
    string m = std::min( { "fooooo", "bar", "hello", "hi" },
                            [](const std::string& s1, const std::string& s2) {
                                cout << endl << s1 << endl << s2 << endl;
                                cout << (s1.size() < s2.size()) << endl;
                                 return s1.size() < s2.size();
                             });
                             
    //cout << endl << m << endl;
                             
}