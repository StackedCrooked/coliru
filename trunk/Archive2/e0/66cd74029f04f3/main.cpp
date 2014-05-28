#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <boost/asio.hpp>

class CallbackTimer
{
public:
  CallbackTimer(const std::function<void()>& callback)
    : callback_(callback),
      currentRepeats_(0),
      strand_(io_),
      timer_(io_),
      thread_(nullptr)
  {}

  ~CallbackTimer()
  {
    cancel();
  }

  void start(size_t intervalMillis, int repeats)
  {
    if (thread_)
    {
      cancel();
    }

    requestedRepeats_ = repeats;
    intervalMillis_ = intervalMillis;
    currentRepeats_ = 0;
    runTimer();

    thread_.reset(new std::thread([this]()
    {
      this->io_.run();
    }));

    thread_->detach();
  }

  void cancel()
  {
    timer_.cancel();
   
    if (thread_ && thread_->joinable())
    {
      thread_->join();
    }
    
    io_.reset();
  }
  
private:

  void runCallback(const boost::system::error_code& e)
  {
    if (e == boost::asio::error::operation_aborted)
    {
      io_.stop();
      return;
    }

    currentRepeats_++;
    callback_();

    if (currentRepeats_ >= requestedRepeats_)
    {
      io_.stop();
      return;
    }

    runTimer();
  }

  void runTimer()
  {
    timer_.expires_from_now(boost::posix_time::millisec(intervalMillis_));
    timer_.async_wait(strand_.wrap(std::bind(&CallbackTimer::runCallback, this, std::placeholders::_1)));
  }
  
private:
  std::function<void()> callback_;
  std::size_t currentRepeats_;
  std::size_t requestedRepeats_;
  std::size_t intervalMillis_;
  boost::asio::io_service io_;
  boost::asio::io_service::strand strand_;
  boost::asio::deadline_timer timer_;
  std::unique_ptr<std::thread> thread_;
};

int main()
{
  CallbackTimer timer([](){});
  timer.start(100000, 5);
  timer.start(100000, 5);
}