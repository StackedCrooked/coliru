#include <algorithm>

struct City {
  bool SortByCityName(const City &c1, const City &c2) {
      return c1.name < c2.name;
  }
  
private:
    std::string name;
};

struct CityList {
    friend bool City::SortByCityName(const City &c1, const City &c2);
    
    void getCitiesByName() {
        std::sort(cities.begin(), cities.end(), sortByCityName);   
    }
    
private:
    std::vector<City> cities;  
};

int main() {
    CityList l;
    l.getCitiesByName();
}