#include <boost/python.hpp>

// Mockup abstract type.
class polygon
{
protected:
 int width, height;
public:
  polygon(int a, int b): width(a), height(b) {}
  virtual int area () = 0;
  virtual ~polygon() = default;
};

// Wrapper to allow calling Python overrides.
struct polygon_wrap
  : polygon, boost::python::wrapper<polygon>
{
  polygon_wrap(): polygon(0, 0) {}
  int area() { return this->get_override("area")(); }
};

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;

  // Expose models.
  python::class_<polygon_wrap, boost::noncopyable>(
      "Polygon", python::init<>())
    .def("area", python::pure_virtual(&polygon::area))
    ;
}