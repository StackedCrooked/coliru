#include <iostream>
struct utf8_iterator: public std::string::iterator
{
    utf8_iterator(const std::string::iterator & it):
        std::string::iterator(it) {}
    utf8_iterator & operator ++() {
        while ((*std::string::iterator::operator++() & 0xC0) == 0x80);
        return *this;
    }
};
int main() {
    using namespace std;
    string s("0", 4);
    s[0] = 'A';
    s[1] = (char)0xD5; // 2 byte begin
    s[2] = (char)0xA5; // 2 byte end
    s[3] = 'Z'; // non-null terminated
    for (utf8_iterator it = utf8_iterator(s.begin()),
        end = utf8_iterator(s.end()); it != end; ++it)
    {
        cout << (it - s.begin()) << endl;
    }
}
