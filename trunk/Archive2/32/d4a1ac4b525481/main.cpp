#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <set>

enum class Direction : char { N='N', E='E', S='S', W='W' };

template <int Rows = 5, int Columns = 5> 
struct Grid {
    using Cell = boost::tuple<int, int>;

    // default starting state
    Cell robot           = { 4, 0 };
    std::set<Cell> cells = { robot, center(), target(center(), Direction::W) }; // robot is there to avoid collisions with blocks

    void move_robot(Direction direction) {
        auto to = target(robot, direction);

        if (offgrid(to))
            throw RobotDied{};

        do_move(robot, direction); // initiate move
        robot = to;
    }

    void display(std::ostream& os) {
        auto character = [&](Cell at) {
            return cells.end()==cells.find(at)
                ? '_' : (robot == at? 'X':'O');
        };

        for (int r=0; r<Rows; ++r) {
            for (int c=0; c<Columns; ++c)
                os << '|' << character({r,c});
            os << "|\n";
        }

        if (succeeded()) {
            std::cout << "GOAL ACHIEVED\n"; // all blocks have been pushed off the grid
        }
    }

    bool succeeded() const {
        assert(!cells.empty());
        assert(cells.end() != cells.find(robot)); // invariant
        return cells.size() == 1;
    }

  private:
    struct RobotDied {};

    static bool offgrid(Cell v) {
        int r,c;
        boost::tie(r,c) = v;
        return (r<0 || c<0 || r>=Rows || c>=Columns);
    };

    static Cell center() { return { Rows/2, Columns/2 }; }

    static Cell target(Cell source, Direction direction) {
        int r,c;
        boost::tie(r,c) = source;

        switch (direction) {
            case Direction::N: return { r-1, c   };
            case Direction::E: return { r  , c+1 };
            case Direction::S: return { r+1, c   };
            case Direction::W: return { r  , c-1 };
            default: throw "tantrum";
        };
    }

    void do_move(Cell at, Direction direction) {
        auto b = cells.find(at);
        if (b == cells.end())
            return;

        cells.erase(b);
        auto to = target(*b, direction);

        if (!offgrid(to)) {
            do_move(to, direction); // cascade
            cells.insert(to);       // re insert the moving block/robot
        }
    }
};

struct command : boost::spirit::qi::symbols<char, Direction> {
    command() {
        add("1000", Direction::N)
           ("0100", Direction::E)
           ("0010", Direction::S)
           ("0001", Direction::W);
    }
};

std::ostream& operator<<(std::ostream& os, Direction d) {
    return os << "'" << static_cast<char>(d) << "'";
}

namespace qi = boost::spirit::qi;

int main() {
    Grid<5, 5> grid;

    grid.display(std::cout);

    boost::optional<Direction> cmd;
    std::string other;

    for(std::cin >> std::noskipws;
        std::cin >> qi::match((command{} || *(qi::char_-qi::eol)) >> qi::eol, cmd, other);
        cmd.reset(), other.clear())
    {
        if (cmd) {
            std::cout << "Command " << *cmd << ":\n";
            grid.move_robot(*cmd);
            grid.display(std::cout);
        } else {
            std::cout << "Ignored unrecognized command '" << other << "'\n";
        }
    }
}
