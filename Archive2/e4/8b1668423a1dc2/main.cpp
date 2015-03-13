#include <iostream>
#include <iomanip>
#include <sstream>

struct round {
    std::string p1;
    std::string p2;
    std::string game;
    int type;
};

std::istream& operator>>(std::istream& in, round& r) {
    return in >> std::quoted(r.p1) >> std::quoted(r.p2) >> r.type >> std::quoted(r.game);
}

std::ostream& operator<<(std::ostream& out, const round& r) {
    return out << std::quoted(r.p1) << ' ' << std::quoted(r.p2) << ' ' << r.type << ' ' << std::quoted(r.game);
}
 
int main() {
    round r = { "player one", "player two", "\"My Cool Game\"", 1 };
    std::stringstream ss;
    ss << r;
    std::cout << "stored as: " << ss.str() << '\n';
    round other;
    ss >> other;
    std::cout << other << '\n' << r << '\n';
}