#include <iostream>
#include <functional>

namespace async {

template <typename T>
using expected_t = std::pair<bool, T>;

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
using callback_t = std::function<void(expected_t<T>)>;

template <typename T, typename U>
using sync_op_t = std::function<expected_t<U>(expected_t<T>)>;

template <typename T, typename U>
using async_op_t = std::function<void(expected_t<T>, callback_t<U>)>;

struct sync_tag {};
struct async_tag {};

template <typename T, typename U>
struct Cont
{
  typedef T value_type;
  typedef U result_type;
  typedef async_op_t<value_type, result_type> async_op_type;
  typedef sync_op_t<value_type, result_type> sync_op_type;

  Cont(sync_op_type p, sync_tag) 
  { 
    op = [=](expected_t<T> v, callback_t<U> cb) {
      cb(p(v));
    };
  }

  Cont(async_op_type op, async_tag) : op(op)
  { 
  }

  template <typename CTX>
  auto operator()(const CTX& ctx) const
    -> Cont<value_type, typename CTX::result_type>
  {
    // todo : type check
    auto tmp_op = op;
    auto new_op = [=](expected_t<value_type> v1, callback_t<typename CTX::result_type> cb) {
      tmp_op(v1, [=](expected_t<result_type> v2) {
        ctx.op(v2, cb);
      });
    };
    return Cont<value_type, typename CTX::result_type> {new_op, async_tag{}};
  }

  template <typename OnComplete, typename OnError>
  callback_t<result_type> subscribe(OnComplete on_complete, OnError on_error) const
  {
    auto tmp_op = op;
    return [=](expected_t<value_type> v) {
      tmp_op(std::move(v), [=](expected_t<result_type> v2) {
        if (result(v2)) on_complete(value(v2));
        else on_error();
      });
    };

  }

  async_op_type op;
};

template <typename T, typename F>
Cont<T, T> swrap(F f)
{
  auto op = [=](expected_t<T> v) {
    if (result(v)) return f(value(v));
    return v;
  };
  return Cont<T, T>{op, sync_tag{}};
}

template <typename T, typename F>
Cont<T, T> awrap(F f)
{
  auto op = [=](expected_t<T> v, callback_t<T> cb) {
    if (result(v)) f(value(v), cb);
    else cb(v);
  };
  return Cont<T, T>{op, async_tag{}};
}

expected_t<int> sync_a(int i)
{
  std::cout << "sync_a" << std::endl;
  return {true, i};
}

expected_t<int> sync_b(int i)
{
  std::cout << "sync_b" << std::endl;
  return {true, i};
}

void async_a(int i, callback_t<int> cb)
{
  std::cout << "async_a" << std::endl;
  cb({true, i});
}

void async_b(int i, callback_t<int> cb)
{
  std::cout << "async_b" << std::endl;
  cb({true, i});
}

int run()
{
  {
    auto op = awrap<int>(async_a)
             (swrap<int>(sync_a))
             (awrap<int>(async_a))
             (swrap<int>(sync_b))
             (awrap<int>(async_a))
             (awrap<int>(async_b))
             .subscribe([=](int v) { std::cout << "success: " << v << std::endl; },
                        [=]() { std::cout << "fail" << std::endl; });
      op(std::make_pair(true, 2));
  }

  return 0;
}

}

int main()
{
  async::run();
  return 0;
}
