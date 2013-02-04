#include <vector>
#include <stdint.h>

namespace Protocol {

template<typename T>
struct Validator
{
    bool validate(const std::vector<uint8_t> &) { return false; }
};

namespace L2 {

struct EthernetProtocol;

template<> struct Validator<EthernetProtocol>
{
    bool validate(const std::vector<uint8_t> &) { return false; }
};

} // namespace L2
} // namespace Protocol


int main()
{
}