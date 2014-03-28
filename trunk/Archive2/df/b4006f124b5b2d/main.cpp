#include <boost/regex.hpp>
#include <boost/cregex.hpp>
#include <vector>

int main()
{
    using namespace boost;

    regex re(".*");

    const std::vector<char> chunkData;

    cregex_iterator reIteratorEnd;
    cregex_iterator reIterator(
            reinterpret_cast<const char*>(chunkData.data()),
            reinterpret_cast<const char*>(chunkData.data()) + chunkData.size(),
            re);
}
