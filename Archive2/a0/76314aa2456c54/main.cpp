#include <memory>
#include <iostream>
#include <type_traits>

template<typename T>
struct unbound_scope {
  template<typename... Args>
  void bind (Args&&... args) {
    if (destruct) ptr->~T ();

    new (&placement) T (std::forward<Args> (args) ...);

    destruct = true;
  }

  ~unbound_scope () {
    ptr->~T ();
  }

  T * operator-> () const { 
    return ptr;
  }

  template<typename U>
  operator U () {
    return static_cast<U> (*ptr);
  }


  typename std::aligned_storage< std::alignment_of<T>::value, sizeof (T) >::type placement;

  bool destruct = false;
  T  * ptr      = reinterpret_cast<T*> (&placement);
};

struct Obj {
   Obj () { std::cerr << "ctor "; }
  ~Obj () { std::cerr << "dtor\n"; }

  void     func () const { std::cerr << n << " "; }
  operator bool () const { return true; }
  int     get_n () const { return --n; }

  static int n;
};

int Obj::n = 3;

int
main (int argc, char *argv[])
{
  unbound_scope<Obj> i; // destruction if the internal `Obj` is of course delayed until the end of this scope, if ever constructed 

  do { i.bind (); i->func (); } while (i && i->get_n ());

}