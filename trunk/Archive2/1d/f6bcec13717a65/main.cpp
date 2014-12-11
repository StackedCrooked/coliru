#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::stringbuf sb("hello");

    sb.pubseekoff(0, std::ios_base::end, std::ios_base::out);

    sb.str("\xE6");

    std::string ret;
    std::copy(std::istreambuf_iterator<char>(&sb),
              std::istreambuf_iterator<char>(),
              std::back_inserter(ret));

    std::cout << ret.length() << std::endl;
}