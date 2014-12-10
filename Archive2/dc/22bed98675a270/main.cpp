#include <iostream>
#include <iterator>

template< class InputIt, class Size, class OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result)
    // Copied from http://en.cppreference.com/w/cpp/algorithm/copy_n
{
    if (count > 0) {
        *result++ = *first;
        for (Size i = 1; i < count; ++i) {
            *result++ = *++first;
        }
    }
    return result;
}

int main()
{
    const char str[]  = "hello world";
    const char *str_end = str + sizeof(str);
    const char oops[] = "zzzzzzzzzzz";
    const char *oops_end = oops + sizeof(oops);

    copy(str, str_end, std::ostream_iterator<char>(std::cout));
}