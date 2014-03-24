#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <functional>

enum class gender_t { male, female, other };

struct osoba
{
    std::string name;
    gender_t gender;
};

static inline gender_t to_gender(char input)
{
    switch(input)
    {
        case 'm': case 'M': return gender_t::male;
        case 'f': case 'F': return gender_t::female;
        case 'o': case 'O': case '*': case '?': return gender_t::other;
    }
    throw std::runtime_error("Unknown gender specification");
}

void brosoba(std::vector<osoba> const& x)
{
    auto pred = [](gender_t g, osoba const& o) { return g == o.gender; };

    using namespace std::placeholders;
    std::cout << "Male: "   << std::count_if(x.begin(), x.end(), std::bind(pred, gender_t::male,   _1)) << ", "
              << "Female: " << std::count_if(x.begin(), x.end(), std::bind(pred, gender_t::female, _1)) << ", "
              << "Other: "  << std::count_if(x.begin(), x.end(), std::bind(pred, gender_t::other,  _1)) << "\n";
}

int main()
{
    std::vector<osoba> a;

    std::string name;
    char gender;
    while (std::cin >> name >> gender)
        a.push_back({name, to_gender(gender)});

    brosoba(a);
}
