class Face {};
class Point {};

typedef double Real;

class Func
{
private:
  const char *m_name, *m_desc;

public:
  Func(const char *name,
       const char *desc) : m_name(name), m_desc(desc) {}

  virtual Real value(Face &f) = 0;

  Real value(Point &p) {return 0.;}

  virtual ~Func() {}
};

class QuadFunc : public Func
{
public:
  QuadFunc() : Func("quad", "Quadratic") {}

  Real value(Face &f) override {return 0.;}
};

int main(int argc, char **argv)
{
  QuadFunc func;

  Face f;
  Point p;

  func.value(f);
  // why doesn't this work?
  func.Func::value(p);

  return 0;
}
