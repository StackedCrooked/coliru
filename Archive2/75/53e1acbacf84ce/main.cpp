#include <boost/function_types/components.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/python.hpp>
#include <boost/python/raw_function.hpp>

namespace trace {
namespace detail {

/// @brief Trace signature type.  Boost.Python requires MPL signature for
///        custom functors.
typedef boost::mpl::vector<
  boost::python::object, // return
  boost::python::object, // frame
  boost::python::object, // event
  boost::python::object  // arg
> trace_signature_type;

/// @brief A noop function for Python.  Returns None.
boost::python::object noop(
  boost::python::tuple /* args */,
  boost::python::dict /* kw */
)
{
  return boost::python::object();
}

} // namespace detail

/// @brief Inject new_locals into the provided frame.
void inject_into_frame_locals(
  boost::python::object frame,
  boost::python::dict new_locals
)
{
  namespace python = boost::python;
  // Force tracing by setting the global tracing function to any non-None
  // function.
  // # if not sys.gettrace():
  if (!PyThreadState_Get()->c_tracefunc)
  {
    // Use the sys.settrace function to prevent needing to re-implement the
    // trace trampoline.
    //   # import sys
    python::object sys(python::handle<>(PyImport_ImportModule("sys")));
    //   # sys.settrace(lambda *args, **keys: None)
    sys.attr("__dict__")["settrace"](python::raw_function(&detail::noop));
  }

  // Create trace function.
  //   # def trace(frame, event, arg):
  python::object trace = python::make_function([new_locals](
        python::object frame,
        python::object /* event */,
        python::object /* arg */
      )
      {
        // Update the frame's locals.
        //   # frame.f_locals.update(new_locals)
        frame.attr("f_locals").attr("update")(new_locals);

        // Set the frame to use default trace, preventing this
        // trace functor from resetting the locals on each trace call.
        //   # del frame.f_trace
        frame.attr("f_trace").del();

        //   # return None
        return boost::python::object();
      },
    python::default_call_policies(),
    detail::trace_signature_type());

  // Set the frame to use the custom trace.
  //   # frame.f_trace = trace
  frame.attr("f_trace") = trace;
}

/// @brief Helper function used to setup tracing to inject the key-value pair
///        into the current frame.
void inject_into_current_frame(
  std::string key,
  boost::python::object value)
{
  // If there is no key, just return early.
  if (key.empty()) return;

  // Create dictionary that will be injected into the current frame.
  namespace python = boost::python;
  python::dict new_locals;
  new_locals[key] = value;

  // Get a handle to the current frame.
  python::object frame(python::borrowed(
    reinterpret_cast<PyObject*>(PyEval_GetFrame())));

  // Set locals to be injected into the frame.
  inject_into_frame_locals(frame, new_locals);
}

} // namespace trace

/// APPROACH 1: has_back_reference

struct foo
{
  // Constructor.
  foo(PyObject* self)
  {
    namespace python = boost::python;
    python::handle<> handle(python::borrowed(self));
    trace::inject_into_current_frame("last_foo", python::object(handle));
  }

  // Boost.Python copy constructor.
  foo(PyObject* self, const foo& /* rhs */)
  {
    namespace python = boost::python;
    python::handle<> handle(python::borrowed(self));
    trace::inject_into_current_frame("last_foo", python::object(handle));
  }
};

namespace boost {
namespace python {
  // Have Boost.Python pass PyObject self to foo during construction.
  template <>
  struct has_back_reference<foo>
    : boost::mpl::true_
  {};
} // namespace python
} // namespace boost

/// APPROACH 2: custom holder

struct bar {};

struct bar_holder
  : public bar
{
  bar_holder(PyObject* self)
  {
    namespace python = boost::python;
    python::handle<> handle(python::borrowed(self));
    trace::inject_into_current_frame("last_bar", python::object(handle));
  }

  bar_holder(PyObject* self, const bar& /* rhs */)
  {
    namespace python = boost::python;
    python::handle<> handle(python::borrowed(self));
    trace::inject_into_current_frame("last_bar", python::object(handle));
  }
};

/// APPROACH 3: custom call policy

struct spam {};

/// @brief CallPolicy that injects a reference to the returned object
///        into the caller's frame.  Expected to only be used as a
//         policy for make_constructor.
template <typename BasePolicy = boost::python::default_call_policies>
struct inject_reference_into_callers_frame
  : BasePolicy
{
  inject_reference_into_callers_frame(const char* name)
    : name_(name)
  {}

  template <typename ArgumentPackage>
  PyObject* postcall(const ArgumentPackage& args, PyObject* result)
  {
    // Chain to base policy.
    result = BasePolicy::postcall(args, result);

    // self is the first argument.  It is an implementation detail that
    // the make_constructor policy will offset access by 1.  Thus, to 
    // access the actual object at index 0 (self), one must use -1.
    namespace python = boost::python;
    python::object self(python::borrowed(
      get(boost::mpl::int_<-1>(), args)));

    // Inject into the current frame. 
    trace::inject_into_current_frame(name_, self);

    return result;
  }

private:
  std::string name_;
};

// Factor functions for the models will be necessary, as custom constructor
// functions will be needed to provide a customization hook for our models.
spam* make_spam() { return new spam(); }

/// APPROACH 4: decorated constructor
//
struct egg {};

namespace detail {

/// @brief A constructor functor that injects the constructed object
///        into the caller's frame.
template <typename Fn>
class inject_constructor
{
public:

  typedef boost::python::object result_type;

public:

  /// @brief Constructor.
  inject_constructor(
    const char* name,
    Fn fn
  )
    : name_(name),
      constructor_(boost::python::make_constructor(fn))
  {}

  /// @brief Initialize the python objet.
  template <typename ...Args>
  result_type operator()(boost::python::object self, Args... args)
  {
    // Initialize the python object.
    boost::python::object result = constructor_(self, args...);

    // Inject a reference to self into the current frame.
    trace::inject_into_current_frame(name_, self);

    return result;
  }

private:
  std::string name_;
  boost::python::object constructor_;
};

} // namespace detail

/// @brief Makes a wrapper constructor (constructor that works with
///        classes inheriting from boost::python::wrapper).
template <typename Fn>
boost::python::object make_inject_constructor(
  const char* name,
  Fn fn)
{
  // Decompose the factory function signature, removing the return type.
  typedef typename boost::mpl::pop_front<
    typename boost::function_types::components<Fn>::type
  >::type components_type;

  // Python constructors take the instance/self argument as the first
  // argument, and returns None.  Thus, inject python::objects into the
  // signature type for both the return and 'self' argument.
  typedef typename boost::mpl::insert_range<
    components_type, 
    typename boost::mpl::begin<components_type>::type,
    boost::mpl::vector<boost::python::object, boost::python::object>
  >::type signature_type;

  // Create a callable python object from inject_constructor.
  return boost::python::make_function(
    detail::inject_constructor<Fn>(name, fn),
    boost::python::default_call_policies(),
    signature_type());
}

egg* make_egg()   { return new egg();  }

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;

  // APPROACH 1: has_back_reference
  python::class_<foo>("Foo", python::init<>());

  // APPROACH 2: custom holder
  python::class_<bar, bar_holder>("Bar", python::init<>());

  // APPROACH 3: custom call policy
  python::class_<spam>("Spam", python::no_init)
    .def("__init__", python::make_constructor(
      &make_spam,
      inject_reference_into_callers_frame<>("last_spam")))
    ;

  // APPROACH 4: decorated constructor
  python::class_<egg>("Egg", python::no_init)
    .def("__init__", make_inject_constructor("last_egg", &make_egg))
    ;
}