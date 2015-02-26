#include <iostream>

class vector
{
  double mx, my;

public:
  vector(double x, double y)
  {
    mx = x; my = y;
  }

  vector operator-() const;
  friend vector operator-(vector &lhs, vector &rhs);
};

vector vector::operator-() const
{
  return vector(-mx, -my);
}

vector operator-(vector &lhs, vector &rhs)
{
  return vector(lhs.mx - lhs.my, rhs.mx - rhs.my);
}

int main()
{
    vector a(0.0, 0.0);
    vector b(0.0, 0.0);
    vector c = a - b;
    return 0;
}