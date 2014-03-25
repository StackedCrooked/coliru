#include <string>
#include <vector>
#include <map>
#include <iostream>

struct osoba
{
    std::string name;
    char gender;
};

void brosoba(std::vector<osoba> const& xs)
{
    std::map<char, size_t> histo;
    for(auto& x : xs)
        histo[x.gender]++;

    for (auto& entry: histo)
        std::cout << entry.first <<  ": " << entry.second << "\n";
}

int main()
{
    std::vector<osoba> a;

    std::string name;
    char gender;
    while (std::cin >> name >> gender)
        a.push_back({name, gender});

    brosoba(a);
}
