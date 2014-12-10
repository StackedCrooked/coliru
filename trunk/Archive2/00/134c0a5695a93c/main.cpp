#include <iostream>
#include <iterator>
#include <sstream>

template< class InputIt, class Size, class OutputIt>
Size copy_n(InputIt first, Size count, OutputIt result)
{
    const InputIt eof {};

    for (; count > 0; --count, ++first, ++result) {
        if (eof == first) {
            break;
        }

        *result = *first;
    }

    return count;
}

int main()
{
    const char *str  = "hello world";
    const char *oops = "zzzzzzzzzzz";

    int numCharsUnwritten;

    numCharsUnwritten = copy_n(str,
                               20,
                               std::ostream_iterator<char>(std::cout));
    std::cout << "\n"
              << numCharsUnwritten << " chars unwritten"
              << "\n";

    std::istringstream iss("hello world");

    numCharsUnwritten = copy_n(std::istreambuf_iterator<char>(iss),
                               20,
                               std::ostream_iterator<char>(std::cout));
    std::cout << "\n"
              << numCharsUnwritten << " chars unwritten"
              << "\n";
}