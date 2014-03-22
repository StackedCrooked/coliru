// Color.h
class Color {
protected:
    int id;
    Color(int id) : id(id) {}
    void operator&(); //undefined
    struct Magic_Trick{ Magic_Trick(); } init;
public:
    Color(const Color& r) : id(r.id) {}
    Color& operator=(const Color& r) {id=r.id; return *this;}
    bool operator==(const Color& r) const {return id==r.id;}
    bool operator!=(const Color& r) const {return id!=r.id;}
    operator int() const {return id;} //so you can still switch on it

    static Color Blue;          
    static Color Red;           
};
static Color::Magic_Trick init;



// Color.cpp
#include "Color.h"

Color Color::Blue(0);
Color Color::Red(1);

Magic_Trick::Magic_Trick() {}
