#include <memory>

template<typename> class FactoryImpl;

template<> class FactoryImpl<void> {
  struct secret { };
  friend class Base;
};

template<typename T>
class FactoryImpl : T {
    template<typename... Args>
    FactoryImpl (Args&&... args)
      : T (std::forward<Args> (args) ... )
    { }

    virtual void _not_allowed (FactoryImpl<void>::secret) override { };
};

class Base {
  public:
    virtual ~Base () { }

  private:
    virtual void _not_allowed (FactoryImpl<void>::secret) = 0;
};

template<typename T, typename... Args>
std::unique_ptr<Base> factory (Args&&... args) {
  return FactoryImpl<T>::create (std::forward<Args> (args) ...);
}


struct Derived : Base {
  Derived ()      { }
  Derived (int i) { }
};


int
main (int argc, char *argv[])
{
    FactoryImpl<Derived> f;
}