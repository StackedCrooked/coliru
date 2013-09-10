#include <utility>

class MoveOnly
{
public:
    MoveOnly() = default;
    MoveOnly(MoveOnly&&) = default;
private:
    /* already implicitly deleted by inclusion of user defined move constructor */
    /* MoveOnly(MoveOnly const&) = delete;
     * MoveOnly& operator=(MoveOnly const&) = delete; */
};

class ContainsMoveOnly
{
public:
    ContainsMoveOnly() = default;
    /* already implicitly included by member element with deleted copy constructor */
    /* ContainsMoveOnly(ContainsMoveOnly&&) = default; */
private:
    MoveOnly mo;
    /* already implicitly deleted by member element with deleted copy constructor */
    /* ContainsMoveOnly(ContainsMoveOnly const&) = delete;
     * ContainsMoveOnly& operator=(ContainsMoveOnly const&) = delete; */
};

int main() {
    auto mo  = MoveOnly();    // okay: uniform initialization, no copy constructor
    /* auto mo = MoveOnly{};  // equivalent to above, but no implicit downcasts of arguments */
    /* auto mo2 = mo;         // error: user deleted copy constructor */
    auto mo2 = std::move(mo); // okay: user defined copy constructor

    auto cmo  = ContainsMoveOnly(); // okay, uniform initialization, no copy constructor
    /* auto cmo2 = cmo;             // error: implicitly deleted copy constructor by ContainsMoveOnly::mo */
    auto cmo2 = std::move(cmo);     // okay, implicitly defined move constructor by ContainsMoveOnly::mo

    return 0;
}
