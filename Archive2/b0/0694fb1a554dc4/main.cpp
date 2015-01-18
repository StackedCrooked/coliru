#include <boost/range/algorithm.hpp>
#include <vector>
#include <list>

using namespace boost;

int main() {
    auto r1 = "I am a range of char";
    auto r2 = "me too!";
    const char* r3[] = { r1, r2 }; // a range of const char*
    auto r4 = std::vector<std::string> { r1, r2 }; // two strings
    auto r5 = std::list<std::string> { begin(r3), end(r3) }; // idem

    std::sort(begin(r3), end(r3)); // sorts by pointer value
    boost::sort(r3);               // sorts by pointer value

    std::sort(begin(r3), end(r3), std::less<std::string>()); // sorts the strings
    boost::sort(r3, std::less<std::string>());               // sorts the strings
}
