#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

template<typename Compare>
class comparator_reference {
public:
    comparator_reference(Compare& x) : ref_(&x) {}
    comparator_reference(const comparator_reference& other) : ref_(other.ref_) {}
    
    comparator_reference& operator=(const comparator_reference& other) {
        ref_ = other.ref_;
        return *this;
    }
    
    Compare& get() const { return *this; }
    operator Compare&() const { return *ref_; }
    
    template<typename T, typename U>
    bool operator()(const T& t, const U& u) {
        return (*ref_)(t, u);
    }
    
private:
    Compare* ref_;
};

template<typename Compare>
comparator_reference<Compare> wrap(Compare& c) {
    return comparator_reference<Compare>(c);
}

struct Point {
  int x, y;
  Point(int xx, int yy) : x(xx), y(yy) {}
  static float dist(const Point &a, const Point &b) {
    const int dx = a.x - b.x, dy = a.y - b.y;
    return sqrtf(dx*dx + dy*dy);
  }
};

// Abstract Point comparison base class.
class Comparator {
public:
  virtual bool operator()(const Point& lhs, const Point& rhs) = 0;
};

// Sorts Points according to distance from the origin.
class DefaultComparator : public Comparator {
public:
  virtual bool operator()(const Point& lhs, const Point& rhs) {
    const Point zero(0,0);
    const float dl = Point::dist(zero, lhs), dr = Point::dist(zero, rhs);
    return dl < dr;
  }
};

// Sorts Points according to distance from a given Point.
class RelativeComparator : public Comparator {
public:
  RelativeComparator(Point p) : _point(p) {}
  virtual bool operator()(const Point& lhs, const Point& rhs) {
    const float dl = Point::dist(_point, lhs), dr = Point::dist(_point, rhs);
    return dl < dr;
  }
private:
  const Point _point;
};

class SortedPoints {
public:
  SortedPoints(Comparator &comp) : _comp(comp) {}

  void push(Point p) {
    _points.push_back(p);
    std::push_heap(_points.begin(), _points.end(), wrap(_comp));
  }

  bool pop(Point &p) {
    if (_points.empty()) {
      return false;
    } else {
      std::pop_heap(_points.begin(), _points.end(), wrap(_comp));
      p = _points.back();
      _points.pop_back();
      return true;
    }
  }

private:
  typedef std::vector<Point> PointList;
  Comparator &_comp;
  PointList _points;
};

int main() {
  DefaultComparator defaultComp;
  RelativeComparator relativeComp(Point(100,100));
  SortedPoints list1(defaultComp);
  SortedPoints list2(relativeComp);
  Point p(0,0);
  list1.push(Point(15,15));
  list1.push(Point(13,13));
  list1.push(Point(5,5));
  printf("List one (relative to 0,0):\n");
  while (list1.pop(p)) {
    printf("%d,%d\n", p.x, p.y);
  }

  list2.push(Point(15,15));
  list2.push(Point(13,13));
  list2.push(Point(5,5));
  printf("List two (relative to 100,100):\n");
  while (list2.pop(p)) {
    printf("%d,%d\n", p.x, p.y);
  }
  return 0;
}
