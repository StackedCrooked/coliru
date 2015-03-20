struct Point0
{
    Point0() : x(), y(), z() {}
    int x, y, z;
};

struct Point1
{
    Point1() : x(-1), y(-1), z(-1) {}
    int x, y, z;
};

struct Point2
{
    Point2() : x(1), y(1), z(1) {}
    int x, y, z;
};

Point0 __fun__()
{
    return Point0();
}

Point1 __gun__()
{
  return Point1();
}

Point2 __hun__()
{
  return Point2();
}

