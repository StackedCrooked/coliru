#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

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

void brosoba(std::vector<osoba> x)
{
    auto end_male   = std::partition(x.begin(), x.end(), [](osoba const& o) { return gender_t::male == o.gender; });
    auto end_female = std::partition(end_male,  x.end(), [](osoba const& o) { return gender_t::female == o.gender; });

    std::cout << "Male: "   << std::distance(x.begin(), end_male)  << ", "
              << "Female: " << std::distance(end_male, end_female) << ", "
              << "Other: "  << std::distance(end_female, x.end())  << "\n";
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
