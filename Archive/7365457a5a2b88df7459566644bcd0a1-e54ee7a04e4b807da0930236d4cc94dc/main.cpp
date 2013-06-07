#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

class Layer
{
public:
    explicit Layer(std::string n, Layer* p = nullptr): name_(n), parent_(p) {}
    std::string name() { return name_; }
    Layer* parent() { return parent_; }
private:
    std::string name_;
    Layer* parent_;
};

// inheriting constructrors (C++11 only, retype constructors for C++98)
class City   : public Layer { using Layer::Layer; };
class Country: public Layer { using Layer::Layer; };
class Planet : public Layer { using Layer::Layer; };

typedef std::multimap<Layer*, Layer*> Atlas;

int main()
{
    Planet Earth("Earth");

    Country USA("United States of America", &Earth);
    Country FRA("France", &Earth);

    std::vector<City> USA_cities = { City("Los Angeles", &USA), City("New York", &USA) };
    std::vector<City> FRA_cities = { City("Bordeaux", &FRA), City("Paris", &FRA) };

    Atlas a;

    a.insert(std::make_pair(&Earth, &USA));
    a.insert(std::make_pair(&Earth, &FRA));

    for (auto& city: USA_cities)
        a.insert(std::make_pair(&USA, &city));

    for (auto& city: FRA_cities)
        a.insert(std::make_pair(&FRA, &city));

    auto countries = a.equal_range(&Earth);
    std::cout << "Countries on planet " << countries.first->first->name() << " :\n";
    for (auto it = countries.first; it != countries.second; ++it) {
         auto country = it->second;
         std::cout << country->name() << " (located on planet " << country->parent()->name() << "), with cities:\n";
         auto cities = a.equal_range(country);
         for (auto jt = cities.first; jt != cities.second; ++jt) { 
              auto city = jt->second;
              std::cout << "     " << city->name() << " (located in country " << city->parent()->name() << ")\n";
         }
         std::cout << "\n";
    }
}