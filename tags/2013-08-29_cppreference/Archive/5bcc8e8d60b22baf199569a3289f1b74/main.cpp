namespace Protocol {


template<typename Prot>
struct Validator
{
    bool validate() const { return true; }
};

namespace L3 {

struct ICMP {};

template<> struct Validator<ICMP>
{
    bool validate() const { return false; }
}

} // namespace L3
} // namespace Protocol


int main()
{
}