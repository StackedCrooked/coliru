#include <boost/python.hpp>

// Mockup types.
class spam {};
class egg  {};

// Factory function that returns boost::python::objects.
boost::python::object make_object(std::string name)
{
  namespace python = boost::python;
  if (name == "spam")     return python::object(spam{});
  else if (name == "egg") return python::object(egg{});
  else                    return python::object();
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;

  // Expose models.
  python::class_<spam>("Spam", python::init<>());
  python::class_<egg>("Egg", python::init<>());

  // Expose factory function.
  python::def("make_object", &make_object);
}