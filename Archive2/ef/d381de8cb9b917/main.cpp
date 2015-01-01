#include <iostream>    // std::cout, std::endl;
#include <functional>  // std::bind
#include <thread>      // std::thread
#include <type_traits> // std::remove_reference
#include <utility>     // std::forward
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

template <typename CompletionToken, typename Signature>
using handler_type_t = typename boost::asio::handler_type<
  CompletionToken, Signature>::type;

template <typename Handler>
using async_result = boost::asio::async_result<Handler>;

/// @brief Helper type used to initialize the asnyc_result with the handler.
template <typename CompletionToken, typename Signature>
struct async_completion
{
  typedef handler_type_t<CompletionToken, Signature> handler_type;

  async_completion(CompletionToken&& token)
    : handler(std::forward<CompletionToken>(token)),
      result(handler)
  {}

  handler_type handler;
  async_result<handler_type> result;
};

template <typename Signature, typename CompletionToken>
typename async_result<
  handler_type_t<CompletionToken, Signature>
>::type
async_func(CompletionToken&& token)
{
  // Initialize the async completion handler and result.
  async_completion<CompletionToken, Signature> completion(
      std::forward<CompletionToken>(token));

  auto handler = completion.handler;
  std::cout << "Spawning thread" << std::endl;
  std::thread([](decltype(handler) handler)
    {
      // The handler will be dispatched to the coroutine's strand.
      // As this thread is not running within the strand, the handler
      // will actually be posted, guaranteeing that yield will occur
      // before the resume.
      std::cout << "Resume coroutine." << std::endl;
      using boost::asio::asio_handler_invoke;
      asio_handler_invoke(std::bind(handler, 42), &handler);
    }, handler).detach();

  // Yield the coroutine.  When this yields, execution transfers back to
  // a handler that is currently in the strand.  The handler will complete
  // allowing other handlers that have been posted to the strand to run.
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Suspend coroutine." << std::endl;
  return completion.result.get();
}

int main()
{
  boost::asio::io_service io_service;

  boost::asio::spawn(io_service,
    [&io_service](boost::asio::yield_context yield)
    {
      // The coroutine itself is not work, so guarantee the io_service has
      // work.
      boost::asio::io_service::work work(io_service);
      std::cout << "Got: " << async_func<void(int)>(yield) << std::endl;
    });

  std::cout << "Running" << std::endl;
  io_service.run();
  std::cout << "Finish" << std::endl;
}