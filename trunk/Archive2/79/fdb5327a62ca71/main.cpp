#include <iostream>
using namespace std;

struct Shape
{
virtual void Draw() = 0;
virtual ~Shape() {}
};

struct Circle : Shape
{
virtual void Draw() { cout << "Draw Circle " << endl; }
private:
string someMember;
};

template < typename ToType , typename FromType>
ToType Dynamic_Cast ( FromType from )
{
return dynamic_cast<ToType>(from);
}

int main()
{
Shape *shape = new Circle;
shape->Draw();

Circle *circle = dynamic_cast<Circle*>(shape);
circle->Draw();

Circle *oneMore = Dynamic_Cast<Circle*,Shape*>(shape); 
oneMore->Draw();

Circle *nope = Dynamic_Cast<Circle*,Shape*>(shape); // <-- Fix this line from Circle *nope = dynamic_cast<Circle*,Shape*>(shape);
//system("pause");
}

