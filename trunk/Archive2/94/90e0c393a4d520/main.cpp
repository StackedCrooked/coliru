#include <type_traits>


    enum class Direction {
        NORTH, EAST, SOUTH, WEST, NUMBER_OF_DIRECTIONS
    };

    constexpr Direction left(Direction d) {
        using ut = std::underlying_type<Direction>::type;
        return (Direction)((ut(d) + ut(Direction::NUMBER_OF_DIRECTIONS)-1)
                           % ut(Direction::NUMBER_OF_DIRECTIONS));
    }

#include <iostream>

std::ostream& operator<<(std::ostream& os, Direction d)
{
    switch(d)
    {
        case Direction::NORTH: return os << "NORTH";
        case Direction::EAST : return os << "EAST";
        case Direction::SOUTH: return os << "SOUTH";
        case Direction::WEST : return os << "WEST";
        default              : return os << "invalid";
    }
}

int main()
{
    Direction d = Direction::NORTH;
    for(int i = 0; i < 2*(int)Direction::NUMBER_OF_DIRECTIONS; ++i)
    {
        std::cout << d << "\n";
        d = left(d);
    }
}