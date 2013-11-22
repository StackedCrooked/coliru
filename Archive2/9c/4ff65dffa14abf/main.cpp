#include <iostream>
#include <exception>

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
      get_wrapper ()->d = true;
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

      return *this;
    }

    template<typename U>
    shared_ptr (shared_ptr<U> const& src)
      : e (src.e)
    {
      static_assert (std::is_convertible<U*, T*>::value,
        "shared_ptr<U> is not compatible with shared_ptr<T>"
      );
    }

    value_wrapper_base* get_wrapper () const {
      try   { std::rethrow_exception (e); }
      catch (value_wrapper_base& ref) { return &ref; }
    }

    T*        get () const { return const_cast<T*> (static_cast<T const*> (get_wrapper ()->ptr)); }
    T* operator-> () const { return get (); }

    std::exception_ptr e;
  };

  template<typename T, typename... Args>
  shared_ptr<T>
  make_shared (Args&&... args)
  {
    return shared_ptr<T> (new T (std::forward<Args> (args) ... ));
  }
}

struct Obj {
  // I could have used delegating ctors,
  // but FUCK that

  Obj (            ) : id (counter++), value (0) { std::cerr << "+Obj_" << id << " = " << value << "\n"; }
  Obj (int        i) : id (counter++), value (i) { std::cerr << "+Obj_" << id << " = " << value << "\n"; }
  Obj (Obj const& s) : id (counter++), value (s.value) { std::cerr << "=Obj_" << id << " = " << value << "\n"; }
  Obj (Obj&&      s) : id (counter++), value (s.value) { std::cerr << ">Obj_" << s.id << " = " << value << "\n"; }
  virtual ~Obj (   ) { std::cerr << "-Obj_" << id << " = " << value << "\n"; };

  virtual void func () { std::cerr << "inside Obj!\n"; }

  int const  id;
  int value = 0;
  static int counter;
};

int Obj::counter = 0;

struct Obj2 : Obj {
  using Obj::Obj;

  virtual void func () { std::cerr << "inside Obj2!\n"; }
};

int
main ()
{
  refp::shared_ptr<Obj> p1;

  {
    auto p2 = refp::make_shared<Obj2> (123);
    p1 = p2;
  }

  p1->func ();
}