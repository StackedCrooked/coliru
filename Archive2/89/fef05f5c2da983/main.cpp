#include <Python.h>
#include <boost/python.hpp>
#include <boost/iterator/iterator_facade.hpp>

class Foo
{
public:
    struct iterator : boost::iterator_facade<iterator, int, boost::single_pass_traversal_tag, int>
    {
        iterator(int i) : current_(i) {}

        bool equal(iterator const& other) const { return current_ == other.current_; }
        int dereference() const { return current_; }
        void increment() { ++current_; }
    private:
        int current_;
    };

    iterator begin() { return 0; }
    iterator end()   { return 3; }
};

BOOST_PYTHON_MODULE(pythonIterator)
{
    boost::python::class_<Foo, boost::noncopyable>("Foo", boost::python::init<>())
        .def("__iter__", boost::python::iterator<Foo, boost::python::return_value_policy<boost::python::return_by_value>>{});
}
