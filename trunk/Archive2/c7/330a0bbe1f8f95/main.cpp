#include <functional>
#include <iostream>

struct Foo
{
    Foo(short id) : id_(id) {}
    short id() const {return id_;}
private:
    short id_;
};

struct Bar : Foo {Bar(short id) : Foo(id) {}};

struct Baz : Foo {Baz(short id) : Foo(id) {}};

namespace std
{
  template <> struct hash<Foo> //hash is not a class template
  { //explicit specialization of non-template std::hash
    size_t operator()(const Foo& foo) const
    {
      return hash<short>()(foo.id()); //std::hash is not a template
    }
  };
}

int main() {
    const Foo a{1};
    const Bar b{{2}};
    const Baz c{3};
    std::hash<Foo> h;
    std::cout<<h(a)<<h(b)<<h(c)<<'\n';
    std::hash<Bar> h2;
    std::hash<Baz> h3;
}