#include <iostream>
#include <functional>

namespace konad {

template <typename T>
using expected_t = std::pair < bool, T > ;

template <typename T>
auto result(T&& t) -> decltype(t.first)
{
  return t.first;
}

template <typename T>
auto value(T&& t) -> decltype(t.second)
{
  return t.second;
}

template <typename T>
using callback_t = std::function < void(expected_t<T>) > ;

template <typename T>
using sync_op_t = std::function < expected_t<T>(expected_t<T>) > ;

template <typename T>
using async_op_t = std::function < void(expected_t<T>, callback_t<T>) > ;

struct sync_tag {};
struct async_tag {};

template <typename T>
struct Cont
{
  Cont(sync_op_t<T> p, sync_tag) 
  { 
    op = [=](expected_t<T> v, callback_t<T> cb) {
      cb(p(v));
    };
  }

  Cont(async_op_t<T> op, async_tag) : op(op)
  { 
  }

  Cont<T> operator()(const Cont<T>& ctx) const
  {
    auto tmp_op = op;
    auto new_op = [=](expected_t<T> v1, callback_t<T> cb) {
      tmp_op(v1, [=](expected_t<T> v2) {
        ctx.op(v2, cb);
      });
    };
    return Cont < T > {new_op, async_tag{}};
  }

  template <typename OnComplete, typename OnError>
  callback_t<T> subscribe(OnComplete on_complete, OnError on_error) const
  {
    auto tmp_op = op;
    return [=](expected_t<T> v) {
      tmp_op(std::move(v), [=](expected_t<T> v2) {
        if (result(v2)) on_complete(value(v2));
        else on_error();
      });
    };

  }

  async_op_t<T> op;
};

template <typename T, typename F>
Cont<T> swrap(F f)
{
  return Cont < T > {f, sync_tag{}};
}

template <typename T, typename F>
Cont<T> awrap(F f)
{
  return Cont < T > {f, async_tag{}};
}

expected_t<int> sync_a(expected_t<int> i)
{
  std::cout << "sync_a" << std::endl;
  return i;
}

expected_t<int> sync_b(expected_t<int> i)
{
  std::cout << "sync_b" << std::endl;
  return i;
}

void async_a(expected_t<int> i, callback_t<int> cb)
{
  std::cout << "async_a" << std::endl;
  cb(i);
}

void async_b(expected_t<int> i, callback_t<int> cb)
{
  std::cout << "async_b" << std::endl;
  cb(i);
}

int run()
{
  {
    auto op = awrap < int > (async_a)
             (swrap < int > (sync_a))
             (awrap < int > (async_a))
             (swrap < int > (sync_b))
             (awrap < int > (async_a))
             (awrap < int > (async_b))
             .subscribe([=](int v) { std::cout << "success: " << v << std::endl; },
                        [=]() { std::cout << "fail" << std::endl; });
      op(std::make_pair(true, 2));
  }

  return 0;
}

}

int main()
{
  konad::run();
  return 0;
}
