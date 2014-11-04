#include <iostream>    // std::cout, std::endl;
#include <functional>  // std::bind
#include <thread>      // std::thread
#include <type_traits> // std::remove_reference
#include <utility>     // std::forward
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

/// @brief Helper type used to initialize the asnyc_result with the handler.
template <typename CompletionToken, typename Signature>
struct async_completion
{
  typedef    typename boost::asio::handler_type<
      CompletionToken, Signature>::type handler_type;
  typedef typename boost::asio::async_result<handler_type> async_result_type;

  async_completion(
    typename std::remove_reference<CompletionToken>::type& token
  )
    : handler(std::forward<CompletionToken>(token)),
      result(handler)
  {}

  handler_type handler;
  async_result_type result;
};

template <typename Signature, typename CompletionToken>
typename async_completion<CompletionToken, Signature>::async_result_type::type
async_func(CompletionToken token)
{
  // Initialize the async completion handler and result.
  async_completion<CompletionToken, Signature> completion(token);

  auto handler = completion.handler;
  std::cout << "Spawning thread" << std::endl;
  std::thread([handler]
    {
      // The handler will be dispatched to the coroutine's strand.
      // As this thread is not running within the strand, the handler
      // will actually be posted, guaranteeing that yield will occur
      // before the resume.
      std::cout << "Resume coroutine." << std::endl;
      using boost::asio::asio_handler_invoke;
      asio_handler_invoke(std::bind(handler, 42), &handler);
    }).detach();

  // Yield the coroutine.  When this yields, execution transfers back to
  // a handler that is currently in the strand.  The handler will complete
  // allowing other handlers that have been posted to the strand to run.
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