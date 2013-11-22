#include <exception>
#include <type_traits>
#include <utility>

namespace refp {
  struct value_wrapper_base {
    value_wrapper_base (void const * ptr, bool d) : ptr (ptr), d (d) { }
    void const * ptr; bool d;
  };

  template<typename T>
  struct shared_ptr {
    struct value_wrapper : value_wrapper_base {
       value_wrapper (T const * ptr)
         : value_wrapper_base (static_cast<void const*> (ptr), false)
       { }

      ~value_wrapper () {
        if (value_wrapper_base::d)
          delete static_cast<T const*> (value_wrapper_base::ptr);
      }
    };

    shared_ptr ()                  = default;
    shared_ptr (shared_ptr&&)      = default;
    shared_ptr (shared_ptr const&) = default;

    shared_ptr (T const* ptr)
      : e (std::make_exception_ptr<value_wrapper> (value_wrapper (ptr)))
    {
      w    = & get_wrapper ();
      w->d = true;
    }

    template<typename U>
    shared_ptr (shared_ptr<U> const& src)
      : e (src.e), w (src.w)
    {
      static_assert (std::is_convertible<U*, T*>::value,
        "shared_ptr<U> is not compatible with shared_ptr<T>"
      );
    }

    shared_ptr<T>& operator= (shared_ptr const& src) {
      return this->operator=<T> (src);
    }

    template<typename U>
    shared_ptr<T>& operator= (shared_ptr<U> const& src)
    {
      static_assert (std::is_convertible<U*, T*>::value,
        "shared_ptr<T> = shared_ptr<U> is not valid!"
      );

      e = src.e;
      w = src.w;

      return *this;
    }

    value_wrapper& get_wrapper () const {
      try   { std::rethrow_exception (e); }
      catch (value_wrapper_base& ref) { return static_cast<value_wrapper&> (ref); }
    }

    T*         get () const { return const_cast<T*> (static_cast<T const*> (w->ptr)); }
    T* operator->  () const { return get (); }

    std::exception_ptr   e;
    value_wrapper_base * w;
  };

  template<typename T, typename... Args>
  shared_ptr<T>
  make_shared (Args&&... args)
  {
    return shared_ptr<T> (new T (std::forward<Args> (args) ... ));
  }
}