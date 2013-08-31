class Rectangle : public Shape
{
    public:
       Rectangle(double Length, double Width) : Shape("Rectangle") { ... } 
};

class Square : public virtual Rectangle
{
  public:
   Square(double side) : Shape("Square"), Rectangle(side, side) {}
};