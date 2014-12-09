#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    std::stringbuf sb("000111222333444555666777888999");
    std::string    buf;

    for (int i = 0; i < 10; ++i, buf.clear()) {
        std::istreambuf_iterator<char> it(&sb);
        if (i & 1) {
            // 25.3.1
            // template<class InputIterator, class Size, class OutputIterator>
            // OutputIterator copy_n(InputIterator first, Size n,
            //                       OutputIterator result);
            //
            // 5   Effects: For each non-negative integer i < n, performs *(result + i) = *(first + i).
            // 6   Returns: result + n.
            // 7   Complexity: Exactly n assignments.
            std::copy_n(it, 3, std::back_inserter(buf));
        }
        else {
            // 25.1
            // 12  In the description of the algorithms operators + and - are used for some of the iterator categories for which
            //     they do not have to be defined. In these cases the semantics of a+n is the same as that of
            //
            //       X tmp = a;
            //       advance(tmp, n);
            //       return tmp;
            std::istreambuf_iterator<char> tmp(it);
            std::advance(tmp, 3);
        }

        std::cout << i << ": " << buf << "\n";
    }
}