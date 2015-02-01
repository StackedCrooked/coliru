#include <set>
#include <iostream>
#include <string>
class sw
{
public:
    explicit sw(const std::string& s) : s_(s) { /* dragons be here */ }
    const std::string& getString() const { return s_; }

    bool operator<(const sw& other) const { return s_ < other.s_; }

private:
    std::string s_;
};

struct Comparator
{
    using is_transparent = std::true_type;

    bool operator()(const sw& lhs, const std::string& rhs) const { return lhs.getString() < rhs; }
    bool operator()(const std::string& lhs, const sw& rhs) const { return lhs < rhs.getString(); }
    bool operator()(const sw& lhs, const sw& rhs) const { return lhs < rhs; }
};

int main() 
{
    std::set<sw, Comparator> swSet{ sw{"A"}, sw{"B"}, sw{"C"} };
    std::cout << std::boolalpha << (swSet.find(std::string("A")) != swSet.end()) << std::endl;
}