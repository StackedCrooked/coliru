// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include <functional>
#include <iostream>

namespace sync {

template <typename T>
using expected_t = std::pair < bool, T >; 

expected_t<int> check_if_even(int i)
{
  if (i % 2 == 0)
    return {true, i};
  return {false, i};
}

void async_auth(int i, std::function<void(expected_t<int>)> cb)
{
  if (i % 4 == 0)
    cb({true, i});
  else
    cb({false, i});
}

void run(int i)
{
  auto ret1 = check_if_even(i);
  if (!ret1.first)
    return;

  async_auth(ret1.second, [](expected_t<int> ret) {
    if (ret.first)
      std::cout << "success. " << ret.second << std::endl;
    else
      std::cout << "fail. " << ret.second << std::endl;
  });
}

}

namespace monad {

template <typename T>
using expected_t = std::pair < bool, T >; 

expected_t<int> check_if_even(int i)
{
  if (i % 2 == 0)
    return {true, i};
  return {false, i};
}

void async_auth(int i, std::function<void(expected_t<int>)> cb)
{
  if (i % 4 == 0)
    cb({true, i});
  else
    cb({false, i});
}

template <typename T>
struct Context
{
  typedef expected_t<T> state_type;

  Context(T v) : t(std::make_pair(true, std::move(v))) { }
  Context(state_type t) : t(std::move(t)) {}

  template <typename U>
  auto operator()(U u) -> decltype(u(std::declval<state_type>()))
  {
      return u(t);
  }

  template <typename OnComplete, typename OnError>
  void subscribe(OnComplete on_complete, OnError on_error)
  {
    if (t.first)
      on_complete(t.second);
    else
      on_error();
  }

  state_type t;
};

template <typename T>
Context<T> context(T t)
{
  return Context<T>(t);
}

template <typename T>
struct AsyncContext
{
  typedef expected_t<T> state_type;
  typedef std::function<void(std::function<void(state_type)>)> cb_type;

  AsyncContext(state_type t) {
    cb = [=](std::function<void(state_type)> c) { c(t); };
  }

  AsyncContext(cb_type cb) : cb(std::move(cb)) {}

  template <typename U>
  auto operator()(U u) -> decltype(u(std::declval<state_type>()))
  {
    return AsyncContext<T>(cb([=](state_type s) {
      return u(s);
    }));
  }

  template <typename OnComplete, typename OnError>
  void subscribe(OnComplete on_complete, OnError on_error)
  {
    cb([=](state_type s) {
      if (s.first)
          on_complete(s.second);
    	else
    	  on_error();
    });
  }

  cb_type cb;
};

template <typename F>
struct Wrap
{
  Wrap(F f) : f(f) {}

  template <typename T>
  auto operator()(T t) -> Context<decltype(t.second)>
  {
    if (t.first)
      return Context<decltype(t.second)>(f(t.second));
    else
      return Context<decltype(t.second)>(t);
  }

  F f;
};

template <typename F>
Wrap<F> wrap(F f) { return Wrap<F>(f); }

template <typename F>
struct AsyncWrap
{
  // void async_auth(int i, std::function<void(expected_t<int>)> cb)
  AsyncWrap(F f) : f(f) {}

  template <typename T>
  auto operator()(T t) -> AsyncContext<decltype(t.second)>
  {
    if (t.first)
      return AsyncContext<decltype(t.second)>(std::bind(f, t.second, std::placeholders::_1));
    else
      return AsyncContext<decltype(t.second)>(t);
  }

  F f;
};

template <typename F>
AsyncWrap<F> async_wrap(F f) { return AsyncWrap<F>(f); }

void run(int i)
{
  auto op = context(i)
    (wrap(check_if_even))
    (async_wrap(async_auth));
  op.subscribe([](int v) { std::cout << "success:" << v << std::endl; },
               []()      { std::cout << "error." << std::endl;  });
}
 
}

int main()
{
  sync::run(2);
  sync::run(4);

  monad::run(2);
  monad::run(4);

  char c;
  std::cin >> c;
	return 0;
}

