#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED

#include <vector>

#ifdef _WIN32
#   include <Windows.h>
#   include "Other.h"
#else
#   include <cstdint>
#   include <cstdlib>
#   include <ctime>

using HDC = uint32_t;
#endif

struct Cell
{
    Cell(int _x=1, int _y=1): x(_x), y(_y) { }

    void Draw(HDC&) const;

    bool operator ==(const Cell& a) const { return (x == a.x && y == a.y); }
    bool operator !=(const Cell& a) const { return !(*this == a); }

    int x;
    int y;
};

struct Shift
{
    Shift(int dx=0, int dy=0) : dx(dx), dy(dy) {}
    int dx, dy;
};

enum class Direction
{
    up, down, left, right
};

enum Figure_Type { I, J, L, O, S, T, Z };

class Figure
{
public:
    /* CONSTRUCTORS */
    Figure();
    Figure(Figure_Type);

    /* MOVEMENT */
    bool        Move(std::vector<Cell>&, Direction&);
    void        Drop(std::vector<Cell>&);
    bool        Rotate(std::vector<Cell>&);

    /* OTHER */
    void        Draw(HDC&);

private:

    /* METHODS */
    void        Generate();
    void        GenerateMasks();
    void        GenerateFigure();
    Figure      GetFigureCopy() const;

    /* DATA */
    char        mask[4][4];
    std::vector<Cell> vCells;
    Figure_Type  type;
    int         rotation;
    Shift       shift;
};

#endif

/*
 * And I'm getting exceptions on vCells.clear() method and (if I comment first
 * line) vCells.push_back(cell) line. Actually every operation with vector /
 * vector iterators crash my program even incrementing iterator, those are just
 * the first so my code isn't running any longer after them.
 *
 * Exception text:
 * **"Unhandled exception at 0x5A4ACCD2 (msvcp110d.dll) in
 *    Tetris_completely_new.exe: 0xC000041D: An unhandled exception was
 *    encountered during a user callback."**
 *
 * And these exceptions are thrown on 217's line of "xutility". I commented it:
 *
 *   ....
 *   // MEMBER FUNCTIONS FOR _Container_base12
 *   inline void _Container_base12::_Orphan_all()
 *     { // orphan all iterators
 *    #if _ITERATOR_DEBUG_LEVEL == 2
 *     if (_Myproxy != 0)
 *       { // proxy allocated, drain it
 *       _Lockit _Lock(_LOCK_DEBUG);
 *
 *       for (_Iterator_base12 **_Pnext = &_Myproxy->_Myfirstiter;
 *         *_Pnext != 0; *_Pnext = (*_Pnext)->_Mynextiter)
 *         **(*_Pnext)->_Myproxy = 0;**    // <------------ THIS LINE
 *       _Myproxy->_Myfirstiter = 0;
 *       }
 *    #endif // _ITERATOR_DEBUG_LEVEL == 2
 *     }
 *   ....
 *
 * Here is how my **Cell struct** looks like:
 */

//And **Figure constructor**:

Figure::Figure()
  : mask {{0}},
    vCells(),
    type((Figure_Type) (rand() % 7)),
    rotation(0),
    shift({0,0})
{
    Generate();
}

//My constructors are using Generate() method, which code is:
void Figure::Generate()
{
    GenerateFigure();
}

void Figure::GenerateFigure()
{
    vCells.clear();
    for(int y = 0; y < 4; y++) {
        for(int x = 0; x < 4; x++) {
            if(mask[y][x] == '0')
                vCells.push_back({4 + x + shift.dx, 20 - y + shift.dy});
        }
    }
}

int main()
{
    srand(time(0));
    Figure fig1;
    Figure fig2;
}
