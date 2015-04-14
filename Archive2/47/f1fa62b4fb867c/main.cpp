#include <iostream>
#include <string>
#include <boost/make_shared.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

class foo
{
public:
  foo(const char* value) : value_(value) {}
  foo(const foo&) = delete;
  foo& operator=(const foo&) = delete;

  bool operator==(const foo& rhs) 
  {
    std::cout << "foo::operator==()" << std::endl;
    return value_ == rhs.value_;
  }

  bool operator!=(const foo& rhs)
  {
    std::cout << "foo::operator!=()" << std::endl;  
    return !(*this == rhs);
  }

  std::string get_value() const     { return value_;  }
  void set_value(std::string value) { value_ = value; }

private:
  std::string value_;
};

boost::shared_ptr<foo> make_foo(const char* value)
{
  return boost::make_shared<foo>(value);
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;
  python::class_<foo, boost::shared_ptr<foo>, boost::noncopyable>(
      "Foo", python::no_init)
    .def("__init__", python::make_constructor(&make_foo))
    .def("__eq__", &foo::operator==)
    .def("__ne__", &foo::operator!=)
    .add_property("value", &foo::get_value, &foo::set_value)
    ;
}