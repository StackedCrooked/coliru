#include <iostream>
using std::cout;
using std::flush;
using std::ostream;

ostream& endLine( ostream& output )
{
    return output << '\n' << flush;
}

int main()
{
    cout << "Testing:";
    cout.operator<<(endLine);
    cout << "abc";
    endLine(cout);
    cout << "def";
    return 0;
}