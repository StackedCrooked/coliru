#include <iostream>
using KxStream = decltype(std::cout);

namespace Blah
{
    class FetchRecord
    {
       friend KxStream& operator<<( KxStream& os, FetchRecord& r );
    protected:
       int mId;
    };
}

namespace Blah {
    KxStream& operator<<( KxStream& os, FetchRecord& r )
    {
       os << r.mId;
       return os;
    }
}



int main() {
    Blah::FetchRecord r;
    std::cout << r;
}