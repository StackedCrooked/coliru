namespace ProtocolStack {

template<typename ProtocolType> struct Validator {
    bool validate() const { return true; }
};

namespace L3 {

struct ICMP { };

template<> struct Validator<ICMP> {
    bool validate() const { return false; }
}

} // namespace L3

} // namespace ProtocolStack


int main()
{
}