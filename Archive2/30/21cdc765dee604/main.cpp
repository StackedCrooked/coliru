#include <boost/python.hpp>

/// @brief boost::python::object that refers to a type.
struct type_object: 
  public boost::python::object
{
  /// @brief If the object is a type, then refer to it.  Otherwise,
  ///        refer to the instance's type.
  explicit
  type_object(boost::python::object object):
    boost::python::object(get_type(object))
  {}

  /// @brief Type identity check.  Returns true if this is the object returned
  ///        returned from type() when passed an instance of an object created
  ///        from a C++ object with type T.
  template <typename T>
  bool is() const
  {
    // Perform an identity check that registartion for type T and type_object
    // are the same Python type object.
    return get_class_object<T>() == static_cast<void*>(ptr());
  }

  /// @brief Type identity check.  Returns true if this is the object is a
  ///        subclass of the type returned returned from type() when passed
  ///        an instance of an object created from a C++ object with type T.
  template <typename T>
  bool is_subclass() const
  {
    return PyType_IsSubtype(reinterpret_cast<PyTypeObject*>(ptr()),
                            get_class_object<T>());
  }

private:

  /// @brief Get a type object from the given borrowed PyObject.
  static boost::python::object get_type(boost::python::object object)
  {
    return PyType_Check(object.ptr())
      ? object 
      : object.attr("__class__");
  }

  /// @brief Get the Python class object for C++ type T.
  template <typename T>
  static PyTypeObject* get_class_object()
  {
    namespace python = boost::python;
    // Locate registration based on the C++ type.
    const python::converter::registration* registration =
          python::converter::registry::query(python::type_id<T>());

    // If registration exists, then return the class object.  Otherwise,
    // return NULL.
    return (registration) ? registration->get_class_object()
                          : NULL;
  }
};

/// @brief Enable automatic conversions to type_object.
struct enable_type_object
{
  enable_type_object()
  {
    boost::python::converter::registry::push_back(
      &convertible,
      &construct,
      boost::python::type_id<type_object>());
  }

  static void* convertible(PyObject* object)
  {
    return (PyType_Check(object) || Py_TYPE(object)) ? object : NULL;
  }

  static void construct(
    PyObject* object,
    boost::python::converter::rvalue_from_python_stage1_data* data)
  {
    // Obtain a handle to the memory block that the converter has allocated
    // for the C++ type.
    namespace python = boost::python;
    typedef python::converter::rvalue_from_python_storage<type_object>
                                                                 storage_type;
    void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

    // Construct the type object within the storage.  Object is a borrowed 
    // reference, so create a handle indicting it is borrowed for proper
    // reference counting.
    python::handle<> handle(python::borrowed(object));
    new (storage) type_object(python::object(handle));

    // Set convertible to indicate success. 
    data->convertible = storage;
  }
};

// Mockup types.
struct A {};
struct B: public A {};
struct C {};

/// Mockup function that receives an object's type.
int func(type_object type)
{
  if (type.is<A>()) return 0;
  if (type.is<B>()) return 1;
  return -1;
}

/// Mockup function that returns true if the provided object type is a
/// subclass of A.
bool isSubclassA(type_object type)
{
  return type.is_subclass<A>();
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;

  // Enable receiving type_object as arguments.
  enable_type_object();

  python::class_<A>("A");
  python::class_<B, python::bases<A> >("B");
  python::class_<C>("C");

  python::def("func", &func);
  python::def("isSubclassA", &isSubclassA);
}