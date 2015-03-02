#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

/// @brief Mockup type.
struct spam
{
  int val;

  spam(int val) : val(val) {}
  bool operator==(const spam& rhs) { return val == rhs.val; }
};

/// @brief Mockup function that operations on a collection of spam instances.
void modify_spams(std::vector<spam>& spams)
{
  for (auto& spam : spams)
    spam.val *= 2;
}

/// @brief smart pointer type that will delegate to a python
///        object if one is set.
template <typename T>
class object_holder
{
public:

  typedef T element_type;

  object_holder(element_type* ptr)
    : ptr_(ptr),
      object_()
  {}

  element_type* get() const
  {
    if (!object_.is_none())
    {
      return boost::python::extract<element_type*>(object_)();
    }
    return ptr_ ? ptr_.get() : NULL;
  }

  void reset(boost::python::object object)
  {
    if (!object.is_none())
    {
      object_ = object;
      ptr_.reset();
    }
  }

private:
  boost::shared_ptr<element_type> ptr_;
  boost::python::object object_;
};

/// @brief Helper function used to extract the pointed to object from
///        an object_holder.  Boost.Python will use this through ADL.
template <typename T>
T* get_pointer(const object_holder<T>& holder)
{
  return holder.get();
}

/// @brief Indexing suite that will resets the element's HeldType to
///        that of the proxy during element insertion.
template <typename Container,
          typename HeldType>
class custom_vector_indexing_suite
  : public boost::python::def_visitor<
      custom_vector_indexing_suite<Container, HeldType>>
{
private:

  friend class boost::python::def_visitor_access;

  template <typename ClassT>
  void visit(ClassT& cls) const
  {
    // Define vector indexing support.
    cls.def(boost::python::vector_indexing_suite<Container>());

    // Monkey patch element setters with custom functions that
    // delegate to the original implementation then obtain a 
    // handle to the proxy.
    cls
      .def("append", make_append_wrapper(cls.attr("append")))
      // repeat for __setitem__ (slice and non-slice) and extend
      ;
  }

  /// @brief Returned a patched 'append' function.
  static boost::python::object make_append_wrapper(
    boost::python::object original_fn)
  {
    namespace python = boost::python;
    return python::make_function([original_fn](
          python::object self,
          HeldType& value)
        {
          original_fn(self, value.get());
          // Store the proxy into the holder.
          value.reset(self[-1]);
        },
      // Call policies.
      python::default_call_policies(),
      // Describe the signature.
      boost::mpl::vector<
        void,           // return
        python::object, // self (collection)
        HeldType>()     // value
      );
  }

  // .. make_setitem_wrapper
  // .. make_extend_wrapper
};

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;

  // Expose spam.  Use a custom holder to allow for transparent delegation
  // to different instances.
  python::class_<spam, object_holder<spam>>("Spam", python::init<int>())
    .def_readwrite("val", &spam::val)
    ;

  // Expose a vector of spam.
  python::class_<std::vector<spam>>("SpamVector")
    .def(custom_vector_indexing_suite<
      std::vector<spam>, object_holder<spam>>())
    ;

  python::def("modify_spams", &modify_spams);
}