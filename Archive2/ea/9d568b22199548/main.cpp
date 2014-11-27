#include <cstdint>
#include <iostream>
#include <initializer_list>

struct Member
{
    template<typename T, typename U>
    Member(U (T::*mp))
        : offset(uintptr_t(&(reinterpret_cast<T*>(0)->*mp)))
        , size(sizeof(reinterpret_cast<T*>(0)->*mp))
    {
    }

    uint16_t offset;
    uint16_t size;
};

bool create(std::string const& pathname, std::initializer_list<Member> keyFragments)
{
    for (auto& i : keyFragments)
        std::cout << "offset:" << i.offset << " size:" << i.size << std::endl;
}

class Record
{
public:
    std::uint16_t id;
    std::uint16_t flags;
    int value;
};

int main(int argc, char **argv) {
    create("foo", { &Record::id, &Record::value });
}
