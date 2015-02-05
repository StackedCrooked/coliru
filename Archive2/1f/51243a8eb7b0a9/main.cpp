#include <iostream>
#include <cmath>

struct Point { double x,y; };

struct Shape {
    virtual ~Shape() {}
    virtual double area() const = 0;
  protected:
    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, Shape const& s) {
        s.print(os);
        return os;
    }
};

struct Circle : Shape {
    Circle(Point c, double r) : centre(c), radius(r) {}

    Point centre;
    double radius;

    virtual double area() const override {
        return (radius*radius) * M_PI;
    }

    virtual ~Circle() { }

  protected:
    virtual void print(std::ostream& os) const override {
        os << "Circle";
    }
};

struct Rectangle : Shape {
    Rectangle(Point tl, Point br) : topleft(tl), bottomright(br) {}

    Point topleft, bottomright;

    virtual double area() const override {
        return std::abs(bottomright.x - topleft.x) * 
               std::abs(bottomright.y - topleft.y);
    }

    virtual ~Rectangle() { }
  protected:
    virtual void print(std::ostream& os) const override {
        os << "Rectangle";
    }

};

struct area_f : boost::static_visitor<double> {
    double operator()(Circle const& r) const {
        return (r.radius*r.radius) * M_PI;
    }
};

int main() {
    Rectangle r { { 1,1 }, { 5,5 } };

    {
        Shape const& shape = r;
        std::cout << shape << ": " << shape.area() << "\n";
    }

    Circle    c { { 10, 10 },  5 };
    {
        Shape const& shape = c;
        std::cout << shape << ": " << shape.area() << "\n";
    }

}


