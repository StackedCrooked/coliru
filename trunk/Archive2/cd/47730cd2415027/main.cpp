#include <iostream>
#include <cmath>

using namespace std;

class Point2d{
public:
    Point2d() {}
    Point2d(double x, double y)
        : X(x), Y(y) {}

    double x() const { return X; }
    double y() const { return Y; }

    /**
     * Returns the norm of this vector.
     * @return the norm
    */
    double norm() const {
        return sqrt( X * X + Y * Y );
    }

    void setCoords(double x, double y) {
        X = x; Y = y;
    }

    // Print point
    friend std::ostream& operator << ( std::ostream& s, const Point2d& p )  {
      s << p.x() << " " << p.y();
      return s;
    }
private:
    double X;
    double Y;
};

class Circle{
public:
   Circle() {}
    /**
     * @param R - radius
     * @param C - center
     */
    Circle(double R, Point2d& C)
        : r(R), c(C) {}

    /**
     * @param R - radius
     * @param X - center's x coordinate
     * @param Y - center's y coordinate
     */
    Circle(double R, double X, double Y)
        : r(R), c(X, Y) {}

    void setCircle(double r, double x, double y) {
        r = r; c.setCoords(x, y);
    }

    Point2d getC() const { return c; }
    double getR() const { return r; }

    size_t intersect(const Circle& C2, Point2d& i1, Point2d& i2) {
        // distance between the centers
        double d = Point2d(c.x() - C2.c.x(),
                c.y() - C2.c.y()).norm();

        // find number of solutions
        if(d > r + C2.r) // circles are too far apart, no solution(s)
        {
            std::cout << "Circles are too far apart\n";
            return 0;
        }
        else if(d == 0 && r == C2.r) // circles coincide
        {
            std::cout << "Circles coincide\n";
            return 0;
        }
        // one circle contains the other
        else if(d + min(r, C2.r) < max(r, C2.r))
        {
            std::cout << "One circle contains the other\n";
            return 0;
        }
        else
        {
            double a = (r*r - C2.r*C2.r + d*d)/ (2.0*d);
            double h = sqrt(r*r - a*a);

            // find p2
            Point2d p2( c.x() + (a * (C2.c.x() - c.x())) / d,
                    c.y() + (a * (C2.c.y() - c.y())) / d);

            // find intersection points p3
            i1.setCoords( p2.x() + (h * (C2.c.y() - c.y())/ d),
                    p2.y() - (h * (C2.c.x() - c.x())/ d)
            );
            i2.setCoords( p2.x() - (h * (C2.c.y() - c.y())/ d),
                    p2.y() + (h * (C2.c.x() - c.x())/ d)
            );

            if(d == r + C2.r)
                return 1;
            return 2;
        }
    }

    // Print circle
    friend std::ostream& operator << ( std::ostream& s, const Circle& C )  {
      s << "Center: " << C.getC() << ", r = " << C.getR();
      return s;
    }
private:
    // radius
    double r;
    // center
    Point2d c;

};


int main(void)
{
    Circle locCircles[5];
    locCircles[0].setCircle(0.000597, 32.684114, -117.180610);
    cout << locCircles[0] << endl;
    cout << "Hello world!" << endl;
    return 0;
}