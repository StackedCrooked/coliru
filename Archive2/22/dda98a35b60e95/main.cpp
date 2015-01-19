#include <string.h>
#include <string>
#include <regex>
#include <iostream>

int main()
{
    const char *text = "123 foobar 456";
    const size_t len = strlen(text);

    const std::regex rx(" (.+)bar");

    std::cmatch what;
    std::regex_search( text, text+len, what, rx);

    for (size_t i = 0; i < what.size(); ++i) {
        std::csub_match sub_match = what[i];
        std::string sub_match_str = sub_match.str();
        std::cout << i << ": " << sub_match_str << '\n';
    }
}
