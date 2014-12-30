#include <vector>
#include <array>
#include <iostream>
static const unsigned WIDTH = 16;
static const unsigned VSCALE = 1;
static const unsigned HEIGHT = WIDTH / VSCALE;
static const unsigned FOOTER = 2;

typedef std::array<char, WIDTH+1> Row;
typedef std::array<Row,HEIGHT - FOOTER> World;

int main() {
    
    std :: vector <World> m_levels;
    
    World levels [] =
    {
        {
            "                ",
            "                ",
            "                ",
            "                ",
            "                ",
            "  ###      ###  ",
            "                ",
            "1122112211221122",
            " 33003300330033 ",
            "1122112211221122",
            " 33003300330033 ",
            "                ",
            "                ",
            "                "
        },
        {
            "       44       ",
            "     555 55     ",
            "    66    66    ",
            "  777      777  ",
            " 66          66 ",
            "  777      777  ",
            "    66#  #66    ",
            "  777 #  # 777  ",
            " 66   #  #   66 ",
            "  777 #  # 777  ",
            "    66#  #66    ",
            "     555 55     ",
            "       44       ",
            "                "
        }
    };

    m_levels .assign (std :: begin (levels), std :: end (levels));
    for(const auto & w : m_levels)
        for(const auto & r : w)
            std::cout << '|' << r.data() << "|\n";
}