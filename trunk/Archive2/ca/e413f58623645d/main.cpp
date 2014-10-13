#include <unordered_set>
#include <vector>

struct point
{
        std::array<int, 3> coords;
        int& x = coords[0];
        int& y = coords[1];
        int& z = coords[2];
 
        point()
        {
        }
 
        point(const int _x, const int _y, const int _z)
        {
                x = _x;
                y = _y;
                z = _z;
        }
        point(const point& p)
        {
                x = p.x;
                y = p.y;
                z = p.z;
        }
        const bool operator==(const point& p) const
        {
                return coords == p.coords;
        }
};
  
namespace std
{
        template<>
        struct hash<point>
        {
                std::size_t operator()(const point& p) const
                {
                        size_t res = 0;
                        for (int i = 0; i < 3; ++i)
                        {
                                res += p.coords[i];
                                res += (res << 10);
                                res ^= (res >> 6);
                        }
                        res += (res << 3);
                        res ^= (res >> 11);
                        res += (res << 15);
                        return res;
                }
        };
}        
        
struct line
{
        std::unordered_set<point> points;
        const bool operator==(const line& p) const
        {
                if (p.points.size() != points.size())
                        return false;
                for (auto& it : p.points)
                        if (points.find(it) == points.end())
                                return false;
                return true;
        }
        std::size_t size()
        {
                return points.size();
        }
};

namespace std
{
        template<>
        struct hash<line>
        {
                std::size_t operator()(const line& l) const
                {
                        size_t res = 0;
                        for (auto& it : l.points)
                                for (int i = 0; i < 3; ++i)
                                {
                                        res += it.coords[i];
                                        res += (res << 10);
                                        res ^= (res >> 6);
                                }
                        res += (res << 3);
                        res ^= (res >> 11);
                        res += (res << 15);
                        return res;
                }
        };
}
 
struct player
{
        int points;
        char icon;
        player()
        {
                points = 0;
        }
};


 
int main()
{
    std::unordered_set<line> moves;
    std::vector<player> players;
}
