#include <iostream>

struct Blah
{
    int x;
    void print_to( std::ostream& stream ) const
    {
        stream << "Blah(" << x << ")";
    }
};

auto operator<<( std::ostream& stream, Blah const& b )
    -> std::ostream&
{
    b.print_to( stream );
    return stream;
}

auto main()
    -> int
{
    using namespace std;

    Blah const o = {42};
    cout << "Here it is: " << o << "." << endl;
}
