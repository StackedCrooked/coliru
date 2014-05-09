#include <iostream>

static int const index = std::ios_base::xalloc();

std::ostream& verbose(std::ostream& stream) {
    stream.iword(index) = 1;
    return stream;
}

std::ostream& noverbose(std::ostream& stream) {
    stream.iword(index) = 0;
    return stream;
}

struct StructA {
    std::string mLongName;
    std::string mShortName;

    inline friend std::ostream& operator << (std::ostream& os, const StructA& rStruct) {
        switch (os.iword(index)) {
            case 1:  return os << rStruct.mLongName;
            case 0:
            default: return os << rStruct.mShortName;
        }
    }
};

int main()
{
    StructA a;
    a.mLongName = "loooooooooooooooooooong names are tedious";
    a.mShortName = "succinctness";

    std::cout << a          << '\n';

    std::cout << verbose;
    std::cout << a          << '\n';

    std::cout << noverbose;
    std::cout << a          << '\n';
}

