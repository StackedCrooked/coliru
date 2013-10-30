#include <iostream>
#include <memory>

template<typename T>
struct initialization_wrapper {
  template<typename... Args>
  static T& get (Args&&... args) {

    if (pointer == false) {
      pointer = std::unique_ptr<T> (
        new T (std::forward<Args> (args)...)
      );
    }

    return *pointer;
  }

  static void release () {
    pointer.reset ();
  }

  static std::unique_ptr<T> pointer;
};

template<typename T> std::unique_ptr<T> initialization_wrapper<T>::pointer;

struct Obj {
  Obj () { std::cerr << "+Obj "; }
  ~Obj () { std::cerr << "-Obj "; }
};

int
main (int argc, char *argv[])
{
  initialization_wrapper<Obj>::get ();
  initialization_wrapper<Obj>::get ();
  initialization_wrapper<Obj>::get ();
  initialization_wrapper<Obj>::release ();
  initialization_wrapper<Obj>::get ();
}
