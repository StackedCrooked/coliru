#include <string>
#include <vector>
#include <unordered_map>

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

class Ship {
    enum ship_type {type_none, type_battleship, type_rowboat, type_count};
    protected:
        coordinates coords;
        ship_type type;
    public:
        Ship(ship_type type);
        void addCoordinates(coordinates new_coords);
};
ship_type ship_type_from_string(const std::string& type)
{
    static const std::unordered_map<std::string,ship_type> map={{"battleship",Ship::type_battleship},{"rowboat",Ship::type_rowboat}};
    auto it = map.find(type);
    if (it == map.end())
        return Ship::type_none;
    else
        return it->second;
}
const char* to_string(ship_type type)
{
    static const char* const map[]={"none","battleship","rowboat"};
    if (type<0 || type>=Ship::type_count)
        return map[Ship::type_none];
    else
        return map[type];
}

std::istream& operator>>(std::istream& in, Ship& new_ship) 
{
    std::string type_string;
    if (!(in >> type_string)) 
        return in;
    ship_type type = ship_type_from_string(type_string);
    if (type == Ship::type_none) 
        return in;
    coordinates coords;
    if (!(in >> coords))
        return in;
    new_ship = Ship(type);
    new_ship.addCoordinates(coords);
    return in;
}

#include <fstream>

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
