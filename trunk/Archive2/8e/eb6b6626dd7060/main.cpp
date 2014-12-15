
#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;

int main()
{
    cout << "std::numeric_limits<std::streampos>::max(): " <<
        std::numeric_limits<std::streampos>::max()  << endl;

    cout << "std::numeric_limits<std::streamsize>::max(): " <<
        std::numeric_limits<std::streamsize>::max()  << endl;

    cout << "std::numeric_limits<uint64_t>::max(): " <<
        std::numeric_limits<uint64_t>::max()  << endl;

    return 0;
}
