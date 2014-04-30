#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

struct coordinates {
    int x;
    int y;
    coordinates() : x(), y() {}
    coordinates(int x, int y) : x(x), y(y) {}
};
std::istream& operator>>(std::istream& in, coordinates& coord)
{return in >> coord.x >> coord.y;}
std::ostream& operator<<(std::ostream& out, coordinates& coord)
{return out << coord.x << ' ' << coord.y;}

enum ship_type {type_none, type_battleship, type_rowboat, type_count};
class Ship {
    protected:
        ship_type type;
        coordinates coords;
    public:
        explicit Ship() : type(type_none), coords() {}
        explicit Ship(ship_type new_type) : type(new_type), coords() {}
        explicit Ship(ship_type new_type, coordinates new_coords) : type(new_type), coords(new_coords) {}
        void setCoordinates(coordinates new_coords) {coords=new_coords;}
};
ship_type ship_type_from_string(const std::string& type)
{
    static const std::unordered_map<std::string,ship_type> map={{"battleship",type_battleship},{"rowboat",type_rowboat}};
    auto it = map.find(type);
    if (it == map.end())
        return type_none;
    else
        return it->second;
}
const char* to_string(ship_type type)
{
    static const char* const map[]={"none","battleship","rowboat"};
    if (type<0 || type>=type_count)
        return map[type_none];
    else
        return map[type];
}

std::istream& operator>>(std::istream& in, Ship& new_ship) 
{
    std::string type_string;
    if (!(in >> type_string)) 
        return in;
    ship_type type = ship_type_from_string(type_string);
    if (type == type_none) 
        return in;
    coordinates coords;
    if (!(in >> coords))
        return in;
    new_ship = Ship(type, coords);
    return in;
}

#include <fstream>
#include <iterator>

int main() {
    std::vector<Ship> list;
    {
        std::ifstream infile("myfile.txt");
        std::istream_iterator<Ship> first(infile), last;
        list.assign(first, last);
        if (infile.eof() == false)
            throw std::runtime_error("could not load data from myfile.txt");
    }
    //tada!
}
