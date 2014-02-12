#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

struct Client
{
    std::string name;
    double x, y;
};

struct ByName
{
    template<class T>
    bool operator () (const T& x, const T& y) const { return x.name < y.name; }
};

int main()
{
    std::vector<Client> clients = {{"John", 1.2, 3.4}, {"John", 2.2, -3.4}, {"Jesus", 0, 0}, {"Matt", 5, 4}, {"Matt", 4, 5}};
    std::vector<Client> accumulated;
    std::sort(clients.begin(), clients.end(), ByName());
    auto i = clients.begin();
    while (i < clients.end())
    {
        auto j = std::upper_bound(i, clients.end(), *i, ByName());
        accumulated.push_back(*i);
        ++i;
        while (i < j)
        {
            accumulated.back().x += i->x;
            accumulated.back().y += i->y;
            ++i;
        }
    }

    for (const auto& c : accumulated)
        std::cout << c.name << ' ' << c.x << ' ' << c.y << std::endl;
}
