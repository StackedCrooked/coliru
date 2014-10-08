#include <iostream>
#include <functional>

namespace monad {

#define USE_T
#ifdef USE_T

template <typename... Args>
using Continuation = std::function<void(Args...)>;

template <typename... Args>
using Continuator = std::function<void(Continuation<Args...>)>;

template <typename... Args>
auto ret(Args... args) -> Continuator<Args...>
{
  return [=](auto continuation) { continuation(args...); };
}

template <typename T1, typename T2>
auto bind(                Continuator<T1, T2> continuator,
          std::function<  Continuator<T1, T2>  (T1, T2)> rest)
  -> Continuator<T1, T2>
{
  return [=] (Continuation<T1, T2> continuation) { 
    auto new_continuation = [=] (T1 t1, T2 t2) { rest(t1, t2)(continuation); };
    continuator(new_continuation);
  };
}

// template <typename... Args>
// auto bind(                Continuator<Args...> continuator,
//           std::function<  Continuator<Args...>  (Args...)> rest)
//   -> Continuator<Args...>
// {
//   return [=] (Continuation<Args...> continuation) { 
//     auto new_continuation = [=] (Args... args) { rest(args...)(continuation); };
//     continuator(new_continuation);
//   };
// }

#else

using Continuation = std::function<void(int, int)>;
using Continuator = std::function<void(Continuation)>;

auto ret(int v, int ec) -> Continuator
{
  return [=](Continuation continuation) { continuation(v, ec); };
}

auto bind(                Continuator continuator,
          std::function<  Continuator (int, int)> rest)
  -> Continuator
{
  return [=] (Continuation continuation) { 
    auto new_continuation = [=] (int v, int ec) { rest(v, ec)(continuation); };
    continuator(new_continuation);
  };
}

#endif

}  // monad 

namespace api {

using namespace std::placeholders;

/////////////////////////////////////////////////////////////////////////////
/// original api
/////////////////////////////////////////////////////////////////////////////
void async_func1(int v, std::function<void(int v1, int v2, int ec)> callback)
{
    if (v < 0)
		callback(0, 0, -1);		/// fail
	else
		callback(v, v, 0);		/// success
}

void async_func2(int v1, int v2, std::function<void(int v, int ec)> callback)
{
	if (v1 + v2 == 4)				
		callback(0, -2);	/// fail
	else
		callback(v1 + v2, 0);		/// success
}

void async_func3(int v, std::function<void(int v, int ec)> callback)
{
	if (v == 2)
		callback(0, -3);	/// fail
	else
		callback(v, 0);		/// success
}

/////////////////////////////////////////////////////////////////////////////
/// monadic
/////////////////////////////////////////////////////////////////////////////
//auto async_func1_m(int v)
#ifdef USE_T

monad::Continuator<int, int, int> async_func1_m(int v)
{
	return std::bind(async_func1, v, _1);
}

monad::Continuator<int, int> async_func2_m(int v1, int v2)
{
	return std::bind(async_func2, v1, v2, _1);
}

monad::Continuator<int, int> async_func3_m(int v)
{
	return std::bind(async_func3, v, _1);
}

#else

auto async_func1_m(int v)
{
	return std::bind(async_func1, v, _1);
}

monad::Continuator async_func2_m(int v1, int v2)
{
	return std::bind(async_func2, v1, v2, _1);
}

//auto async_func3_m(int v)
monad::Continuator async_func3_m(int v)
{
	return std::bind(async_func3, v, _1);
}

#endif
	
}  // api

namespace no_monad {

using namespace api;

void run_noexcept(int v, std::function<void(int, int)> callback)
{
	async_func1(v, [=] (auto v1, auto v2, auto ec) {
	async_func2(v1, v2, [=] (auto v, auto ec) {
	async_func3(v, [=] (auto v, auto ec) {
							callback(v, ec);
	});});});
}

void run(int v, std::function<void(int,int)> callback)
{
	async_func1(v, [=] (auto v1, auto v2, auto ec) {
			if (!ec)
				async_func2(v1, v2, [=] (auto v, auto ec) {
					if (!ec)
						async_func3(v, [=] (auto v, auto ec) {
							callback(v, ec);
						});
					else
						callback(0, ec);
				});
			else
				callback(0, ec);	
	});
}
	
}  // no_monad 

namespace use_monad {

using namespace api;

void run(int v, std::function<void(int, int)> callback)
{
 	auto f = 
 					monad::bind<int, int>(async_func3_m(v), 			[=] (int v, int ec) { 
 	return 	monad::bind<int, int>(async_func2_m(v, v),	  [=] (int v, int ec) { 
 	return 	monad::bind<int, int>(async_func3_m(v),				[=] (int v, int ec) { 
 											return monad::ret(v, ec);
 	});});});

  f(callback);
}


// void run(int v, std::function<void(int ec)> callback)
// {
// 	auto f = 
// 					monad::bind(async_func1(v), 			[=] (auto v1, auto v2) {
// 	return 	monad::bind(async_func2(v1, v2),	[=] (auto v) {
// 	return 	monad::bind(async_func3(v),				[=] () {
// 											callback(0); 
// 	});});})
// 					.on_error([=] (auto ec) { callback(ec); });
// 
// 	f();
// }
	
}  // use_monad 

int main()
{
	std::cout << "= continuation sample ========" << std::endl;
	no_monad::run_noexcept(-1, [] (auto v, auto ec) { std::cout << "no monad. no except. result:" << v << ", error: " << ec << std::endl; });
	no_monad::run_noexcept(2,  [] (auto v, auto ec) { std::cout << "no monad. no except. result:" << v << ", error: " << ec << std::endl; });
	no_monad::run_noexcept(1,  [] (auto v, auto ec) { std::cout << "no monad. no except. result:" << v << ", error: " << ec << std::endl; });
	no_monad::run_noexcept(4,  [] (auto v, auto ec) { std::cout << "no monad. no except. result:" << v << ", error: " << ec << std::endl; });
	std::cout << std::endl;

	no_monad::run(-1, [] (auto v, auto ec) { std::cout << "no monad. result:" << v << ", error: " << ec << std::endl; });
	no_monad::run(2,  [] (auto v, auto ec) { std::cout << "no monad. result:" << v << ", error: " << ec << std::endl; });
	no_monad::run(1,  [] (auto v, auto ec) { std::cout << "no monad. result:" << v << ", error: " << ec << std::endl; });
	no_monad::run(4,  [] (auto v, auto ec) { std::cout << "no monad. result:" << v << ", error: " << ec << std::endl; });
	std::cout << std::endl;

	use_monad::run(-1, [] (auto v, auto ec) { std::cout << "use monad. no except. result:" << v << ", error: " << ec << std::endl; });
	use_monad::run(2,  [] (auto v, auto ec) { std::cout << "use monad. no except. result:" << v << ", error: " << ec << std::endl; });
	use_monad::run(1,  [] (auto v, auto ec) { std::cout << "use monad. no except. result:" << v << ", error: " << ec << std::endl; });
	use_monad::run(4,  [] (auto v, auto ec) { std::cout << "use monad. no except. result:" << v << ", error: " << ec << std::endl; });
	std::cout << std::endl;
}
