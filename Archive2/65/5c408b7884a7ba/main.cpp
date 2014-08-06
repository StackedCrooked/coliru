class Point  {
public:
  constexpr double setX(double newX) { return x = newX; }
  constexpr double getX() const { return x; }
private:
  double x {}; // without init: "error: constexpr function never produces a constant expression [-Winvalid-constexpr]"
};

constexpr Point f()
{
    Point p;
    p.setX(1.0);
    return p;
}

int main()
{
    auto constexpr p = f();        
    static_assert(p.getX() == 1.0, "");
}
