#include <iomanip>
#include <iostream>
#include <vector>

class Whine
{
public:

    Whine()
    {
        std::clog << this << " Whine::Whine()\n";
    }

    Whine(const Whine &w)
    {
        std::clog << this << " Whine::Whine(const Whine &w), with &w == " << &w << '\n';
    }

    Whine & operator = (const Whine &w)
    {
        std::clog << this << " Whine::operator=(const Whine &w), with &w == " << &w << '\n';
        return *this;
    }

    ~Whine()
    {
        std::clog << this << " Whine::~Whine()\n";
    }
};

int main()
{
    std::clog << '\n' << std::setw(79) << std::setfill('*') << std::left << "Vector of Whine #1 behavior " << '\n';

    {
        std::vector<Whine> vw1;

        std::clog << "vw1.resize(10)\n";
        vw1.resize(10);
        std::clog << "vw1.size() == " << vw1.size() << '\n';
        std::clog << "vw1.capacity() == " << vw1.capacity() << '\n';
    }

    std::clog << '\n' << std::setw(79) << std::setfill('*') << std::left << "Vector of Whine #2 behavior " << '\n';

    {

        std::vector<Whine> vw2;

        std::clog << "vw2.reserve(10)\n";
        vw2.reserve(10);
        std::clog << "vw2.size() == " << vw2.size() << '\n';
        std::clog << "vw2.capacity() == " << vw2.capacity() << '\n';
    }
}
