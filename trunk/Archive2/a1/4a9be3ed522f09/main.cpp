#include <functional>
#include <string>
#include <unordered_set>
#include <unordered_map>

class Base
{
public:
  template <class T>
  using const_pset = std::unordered_set<const T *, std::hash <T *> >;
  template <class T, class U>
  using const_pmap = std::unordered_map<const T *, U, std::hash <T *>>;
};

class A : public Base
{
public:
  std::size_t hash () const
  {
    std::hash<std::string> hashfn;
    return hashfn (str);
  }
  bool operator== (const A &a) const { return str == a.str; }
  std::string str;
};

namespace std
{
    template <>
    struct hash<A*>
    {
      typedef const A* argument_type;
      typedef std::size_t result_type;

      result_type operator () (const argument_type op) const
      {
            return op->hash ();
      }
    };   
}

extern const A* get_a ();

typedef Base::const_pmap<A, Base::const_pset<A> > mapA;

int work (mapA &mapa)
{
  const A *a = get_a ();
  mapa[a];
  return 42;
}

int main() {}