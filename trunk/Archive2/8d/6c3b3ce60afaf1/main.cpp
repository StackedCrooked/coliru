#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory> 
#include <map>
#include <boost/variant.hpp>

using variant_t = boost::variant<int, float, bool>;

template<size_t... Ns> struct int_seq { };
 
template<          size_t... Ns> struct make_int_seq;
template<size_t N, size_t... Ns> struct make_int_seq<N, Ns...> : make_int_seq<N-1, N, Ns...> { };
template<          size_t... Ns> struct make_int_seq<0, Ns...> { typedef int_seq<0, Ns...> type; };
 

struct callback {
  virtual void forward (std::vector<variant_t> const&) const = 0;
};

template<typename Ret, typename... Args>
class impl_callback : callback {

  impl_callback (Ret(*fp)(Args...))
    : fptr (fp)
  { }

  virtual void forward (std::vector<variant_t> const& vec) const {
    forward (vec, typename make_int_seq<sizeof... (Args)-1>::type { });
  }

  template<size_t... Ns>
  void forward (std::vector<variant_t> const& args, int_seq<Ns...>) const {

    if (args.size () < sizeof... (Args))
      throw std::invalid_argument ("");

    fptr (boost::get<Args> (args[Ns]) ...);
  }

  template<typename _Ret, typename... _Args>
  friend std::unique_ptr<callback> make_callback (_Ret(*)(_Args...));

  Ret(*fptr)(Args...);
};


template<typename Ret, typename... Args>
std::unique_ptr<callback>
make_callback (Ret(*f)(Args...))
{
  return std::unique_ptr<callback> ( new impl_callback <Ret, Args...> (f) );
}

struct callback_map {

  template<typename F>
  void add_callback (std::string const& key, F f)
  {
    callbacks[key].push_back (make_callback (f));
  }

  void something_happened (std::string const& key, std::vector<variant_t> const& vec) {
    auto const cit = callbacks.find (key);

    if (cit == callbacks.end ())
      return;

    for (auto const &cb : cit->second) {
      cb->forward (vec);
    }
  }

  std::map<
    std::string,
    std::vector<std::unique_ptr<callback>>
  > callbacks;
};

// -------------------------------------------------------------------------------------

void foo (int i) {
  std::cout << "foo (int) -> {" << i << "}\n";
}

void bar(int i, float f, bool b)
{
  std::cout << "bar (int,float,bool) -> {" << i << ", " << f << ", " << b << "}\n";
}

void baz(int i, float f, bool b)
{
  std::cout << "baz (int,float,bool) -> {" << i << ", " << f << ", " << b << "}\n";
}

int
main (int argc, char *argv[])
{
  callback_map cm;

  cm.add_callback ("hello", bar);
  cm.add_callback ("hello", baz);
  cm.add_callback ("world", foo);

  cm.something_happened ("world", { { 1 }, { 2.3f }, { false } });
  cm.something_happened ("hello", { { 1 }, { 2.3f }, { false } });
}