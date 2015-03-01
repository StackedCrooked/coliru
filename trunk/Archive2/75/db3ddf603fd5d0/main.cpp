#include <iostream>
using namespace std;

//rectangle class declaration
class Rectangle
{
public:
    //constructors
    Rectangle(int width, int height);
    ~Rectangle(){}
    
    //overload class function drawShape
    void DrawShape() const;
    void DrawShape(int aWidth, int aHeight) const;
    
private:
    int itsWidth;
    int itsHeight;
};

//constructor implementation
Rectangle::Rectangle(int width, int height)
{
    itsWidth;
    itsHeight;
}


//overloaded DrawShape - takes no values
//Draws based on current class member values
void Rectangle::DrawShape() const
{
    DrawShape(itsWidth, itsHeight);
}


//overloaded DrawShape - takes two values
//Draws shape based on the parameters
void Rectangle::DrawShape(int width, int height) const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << "*";
        }
        cout << "\n";
    }
}

//Driver program to demonstrate overloaded functions
int main()
{
    //Initialize a rectangle to 30, 5
    Rectangle theRect(30, 5);
    cout << "DrawShape(): \n";
    theRect.DrawShape();
    cout << "\nDrawShape(40, 2): \n";
    theRect.DrawShape(40, 2);
    return 0;
}