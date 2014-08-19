// Try to solve level 34 of "Game about Squares"
// Screenshot: http://i.imgur.com/sz01NWa.png
//
// Initial code and probably full of bugs.

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <vector>


enum Color
{
    White, Purple, Red, Blue
};


enum Direction
{
    None, Up, Left, Right, Down
};

struct Point
{
    Point(int x, int y) : xy_(x, y) {}

    int x() const { return xy_.first; }

    int y() const { return xy_.second; }

private:
    friend bool operator<(const Point& lhs, const Point& rhs)
    {
        return lhs.xy_ < rhs.xy_;
    }

    friend bool operator==(const Point& lhs, const Point& rhs)
    {
        return lhs.xy_ == rhs.xy_;
    }

    std::pair<int, int> xy_;
};


// "move" a point in a direction
// returns a copy of the original point with delta applied
Point move(Point p, Direction d)
{
    switch (d)
    {
        case None : return p;
        case Up   : return Point(p.x(), p.y() - 1);
        case Down : return Point(p.x(), p.y() + 1);
        case Left : return Point(p.x() - 1, p.y());
        case Right: return Point(p.x() + 1, p.y());
    }
}

struct Square
{
    Square(Color color, Point point, Direction direction) :
        color_(color),
        position_(point),
        direction_(direction)
    {
    }

    Color color() const
    {
        return color_;
    }

    Point position() const
    {
        return position_;
    }

    Direction direction() const
    {
        return direction_;
    }

    // turn to a direction
    void turn_to(Direction d)
    {
        if (d != None)
        {
            direction_ = d;
        }
    }

    // moves the square one step
    void move_one()
    {
        position_ = move(position(), direction());
    }

private:
    Color color_;
    Point position_;
    Direction direction_;
};

struct Surface
{
    Surface& add_arrow(Point p, Direction d)
    {
        arrows_[p] = d;
        return *this;
    }

    Surface& add_target(Point p, Color color)
    {
        targets_.erase(p);
        targets_.insert(std::make_pair(p, color));
        return *this;
    }

    Color color_at(Point p) const
    {
        auto it = targets_.find(p);
        if (it != targets_.end())
        {
            return it->second;
        }
        return White;
    }

    Direction arrow_at(Point p) const
    {
        auto it = arrows_.find(p);
        if (it != arrows_.end())
        {
            return it->second;
        }
        return None;
    }

private:
    std::map<Point, Direction> arrows_;
    std::map<Point, Color> targets_;
};


template<typename SquareIt>
bool is_solved(const Surface& surface, SquareIt b, SquareIt e)
{
    for (auto it = b; it != e; ++it)
    {
        auto& square = *it;
        if (surface.color_at(square.position()) != square.color())
        {
            return false;
        }
    }
    return true;
}


// move a square on surface
// - moves the square one position according its arrow direction
// - changes the arrow direction if new surface position has an arrow
void move(const Surface& surface, Square& square)
{
    square.move_one();
    square.turn_to(surface.arrow_at(square.position()));
}

int main()
{
    auto surface = Surface()
        .add_arrow(Point(0, 0), Down)
        .add_arrow(Point(3, 0), Left)
        .add_arrow(Point(0, 1), Right)
        .add_arrow(Point(2, 2), Up)
        .add_target(Point(2, 1), Red)
        .add_target(Point(2, 1), Purple)
        .add_target(Point(2, 3), Blue)
        ;

    std::vector<Square> squares = {
        { Purple, Point(0, 0), Down   },
        { Blue,   Point(0, 3), Left   },
        { Red,    Point(0, 1), Right  }
    };

    enum move_id { move_blue, move_purple, move_red };

    // according the the stats page the puzzle can be solved in 33 moves
    // we generate a little more
    enum { num_moves = 33 + 2 };

    // generate random moves
    auto generate_random_moves = [](int count){
        std::vector<move_id> result;
        result.reserve(count);
        while (result.size() < result.capacity())
        {
            result.push_back(static_cast<move_id>(result.size() % 3));
        }

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::shuffle(result.begin(), result.end(), generator);
        return result;
    };

    enum { max_tries = 100000 };

    for (long i = 0; i != max_tries; ++i)
    {

        // note: using random moves each cycle is worst than brute force.
        // might need improvement a solution is not found after a few seconds.
        std::vector<move_id> moves = generate_random_moves(num_moves);

        // todo:
        for (move_id id : moves)
        {
            move(surface, squares[id]);
            if (is_solved(surface, begin(squares), end(squares)))
            {
                std::cout << "Found solution: ";
                for (move_id id : moves)
                {
                    switch (id)
                    {
                        case move_blue: std::cout << " blue"; break;
                        case move_red: std::cout << " red"; break;
                        case move_purple: std::cout << " purple"; break;
                    }
                }
                std::cout << std::endl;
                return 0;
            }
        }
    }

    std::cout << "Failed after " << max_tries << " tries" << std::endl;
}
