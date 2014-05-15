#include <iostream>
using namespace std;

class coord
{
public:
    coord() : x_(0), y_(0) { }
    coord(float x, float y) : x_(x), y_(y) { }
    
    float x() const { return x_; }
    float y() const { return y_; }
    void x(float x) { x_ = x; }
    void y(float y) { y_ = y; }
private:
    float x_;
    float y_;
};

/* Note: hitboxes are rectangles that are not rotated,
   in other words trivializing their intersection.
   This also means they are expressable using just
   2 points.*/
class hitbox
{
public:
    hitbox(coord top_left, coord bottom_right)
        : tl_(top_left), br_(bottom_right)
    {
    }
    
    /* returns: true if ANY part of rhs is inside of *this,
                false otherwise */
    bool intersect(const hitbox& rhs);
    
private:
    coord tl_; // top left
    coord br_; // bottom right
};

bool hitbox::intersect(const hitbox& rhs)
{
    /* See: http://silentmatt.com/rectangle-intersection/
       for visualization of intersection.
       This assumes origin is the top-left corner, and that
       positive X extends to the right and positive Y downwards */
    if (tl_.x() <= rhs.br_.x() &&
        br_.x() >= rhs.tl_.x() &&
        tl_.y() <= rhs.br_.y() &&
        br_.y() >= rhs.tl_.y())
        return true;
    return false;
}

int main()
{
    /* see: http://i.imgur.com/gYsieof.png */
    hitbox A(coord(2, 10), coord(4, 12));
    hitbox B(coord(4, 6), coord(7, 13));
    hitbox C(coord(6, 4), coord(8, 7));
    
    cout << "A intersect B: " << (A.intersect(B) ? "true" : "false") << endl;
    cout << "A intersect C: " << (A.intersect(C) ? "true" : "false") << endl;
    cout << "B intersect A: " << (B.intersect(A) ? "true" : "false") << endl;
    cout << "B intersect C: " << (B.intersect(C) ? "true" : "false") << endl;
    cout << "C intersect A: " << (C.intersect(A) ? "true" : "false") << endl;
    cout << "C intersect B: " << (C.intersect(B) ? "true" : "false") << endl;
}
