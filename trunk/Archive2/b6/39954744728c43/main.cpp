#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>

#include <iostream>
#include <thread>
#include <type_traits>

namespace asio = ::boost::asio;
namespace chrono = ::boost::chrono;

template <class Handler>
struct handler_wrapper_helper
{
public:
  handler_wrapper_helper (Handler const& handler) : handler_ (handler) {}
  handler_wrapper_helper (Handler&& handler) : handler_ (std::move (handler)) {}

  template <typename... Args>
  auto operator ()(Args ...args)
  {
      return handler_ (std::forward<Args> (args)...);
  }

private:
  Handler handler_;

  template <class Function>
  friend void asio_handler_invoke (Function function,
      handler_wrapper_helper* context)
  {
    using boost::asio::asio_handler_invoke;
    asio_handler_invoke (std::forward<Function> (function), &context->handler_);
  }
};

template <class Handler>
auto
handler_wrapper (Handler&& handler)
{
	return handler_wrapper_helper<std::decay_t<Handler>> (
	  std::forward<Handler> (handler));
}

template <typename Timer, typename Token>
void
my_timer (Timer& timer, Token&& token)
{
  typename asio::handler_type<
      Token, void (::boost::system::error_code const)
    >::type handler (std::forward<Token> (token));

  asio::async_result<decltype (handler)> result (handler);

#if 1 // Another alternative
  timer.async_wait (handler_wrapper (handler));
#else
  timer.async_wait (handler);
  timer.get_io_service().post (
    [handler] () mutable
    {
      boost::system::error_code error;
      // Handler must be invoked through asio_handler_invoke hooks
      // to properly synchronize with the coroutine's execution
      // context.
      using boost::asio::asio_handler_invoke;
      asio_handler_invoke (
        [handler, error] () mutable { return handler (error); },
        &handler
      );
    }
  );
#endif

  result.get (); // Got forced_unwind exception here.

  asio::steady_timer (timer.get_io_service (), chrono::milliseconds (50))
    .wait ();
}

int main ()
{
  asio::io_service io;
  asio::steady_timer timer (io, chrono::microseconds (1));

  asio::spawn (io,
    [&] (asio::yield_context yield)
    {
    	try
      {
        std::cout << "my_timer enter\n";
        my_timer (timer, yield);
        std::cout << "my_timer returns\n";
      }
      catch (const boost::coroutines::detail::forced_unwind&)
      {
        std::cout << "Caught forced_unwind!" << std::endl;
        throw;
      }
    }
  );

  std::thread thr { [&io] { io.run (); } };
  io.run ();
  thr.join ();

  return 0;
}