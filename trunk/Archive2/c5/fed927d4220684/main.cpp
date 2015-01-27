#include <iostream>
#include <cmath>

struct coord {
    int x,y;
};

bool tileTrace(coord p_start, coord p_end)
{
    int sx = p_start.x;
    int sy = p_start.y;
    int ex = p_end.x;
    int ey = p_end.y;
    int dx = fabsf(ex - sx);
    int dy = fabsf(ey - sy);

    int _x = sx, _y = sy;
    int x_inc = (ex > sx) ? 1 : -1;
    int y_inc = (ey > sy) ? 1 : -1;
    int error = dx - dy;

    for(int n = dx + dy; n > 0; n--) {
        //Tile& t = m_tiles[_y * m_width + _x];
        //if(!(t.m_walkable)) return false;
        if(error < 0) {
            _y += y_inc;
            error += dx;
        } else {
            _x += x_inc;
            error -= dy;
        }
        std::cout << _x << ','<<_y << "   ";
    }
    return true;
}

int main() {
    tileTrace({0,0},{6,2});
    std::cout << '\n';
    tileTrace({0,0},{-6,0});
    std::cout << '\n';
    tileTrace({0,0},{0,-2});
    std::cout << '\n';
    tileTrace({0,0},{-1,-1});
}