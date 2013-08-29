#include <array>
#include <stdint.h>

typedef std::array<uint8_t, 6> MAC;

class Id
{
public:
    Id() : mBytes() {}

    Id(uint64_t inNumber, const MAC & inMAC) :
        mData {inNumber, inMAC}
    {
    }

    typedef char Bytes[14];
    union
    {
        Bytes mBytes;
        struct
        {
            uint64_t mNumber;
            MAC mMAC;
        } mData;
    };
};

int main()
{
    uint64_t num {};
    MAC mac = MAC();

    Id id {num, mac};
    Id id2;
}