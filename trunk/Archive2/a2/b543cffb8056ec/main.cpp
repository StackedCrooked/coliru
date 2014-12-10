#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    std::stringbuf sb("aaaaabbbbbccccc");
    std::string    buf;

    for (int i = 0; i < 3; ++i, buf.clear()) {
        std::copy_n(std::istreambuf_iterator<char>(&sb),
                    5,
                    std::back_inserter(buf));

        std::cout << buf << "\n";
    }

    sb.pubseekoff(0, std::ios_base::beg);

    for (int i = 0; i < 3; ++i, buf.clear()) {
        std::istream is(&sb);

        std::copy_n(std::istream_iterator<char>(is),
                    5,
                    std::back_inserter(buf));

        std::cout << buf << "\n";
    }
}