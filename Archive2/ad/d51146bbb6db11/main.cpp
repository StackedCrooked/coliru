#include <string>

class ructor
{
    std::string name;

    ructor() : name("a") {}

    static const ructor() { return ructor(); }
};      // ^^^^^^^^^^^^ lol