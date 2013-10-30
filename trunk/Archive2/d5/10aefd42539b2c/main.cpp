#include <chrono>
#include <memory>
#include <thread>

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/bind.hpp>

// proxy_guard is a type that provides RAII semantics with shared reference
// counting.  While it would be ideal to just use two std::shared_ptr, it is
// unspecified as to which shared_ptr would be referenced by the internal
// weak_ptr from objects inheriting from enable_shared_from_this.
template <typename T>
class proxy_guard
{
public:

  typedef T element_type;

  proxy_guard() = default;

  template <typename Y, typename S, typename D>
  proxy_guard(Y* p, S s, D d)
    : p_(p),
      guard_(static_cast<void*>(&p), // Perform type erasure on p so that
                                     // its weak_ptr is not set.
            [p, d](void*) { d(p); })
    {
      s(p);
    }
  
  void swap(proxy_guard& r)
  {
    using std::swap;
    swap(p_, r.p_);
    swap(guard_, r.guard_);
  }
  
  void reset()          { proxy_guard().swap(*this); }  
  T* get() const        { return p_; }
  T& operator*() const  { return *p_; }
  T* operator->() const { return p_; }
  
  explicit operator bool() const { return p_; }
 
private:
  T* p_;
  std::shared_ptr<void> guard_;
};

/// @brief Mockup class demonstrating the decoupling of object lifespan in
///        asynchronous call chains from RAII semantics provided to the end
///        user.
class ticker
  : public std::enable_shared_from_this<ticker>,
    private boost::noncopyable
{
public:

  static proxy_guard<ticker>
  create(boost::asio::io_service& io_service)
  {
    // Create shared_ptr that manages lifetime.
    std::shared_ptr<ticker> managed(
      new ticker(io_service),
      [](ticker* ptr)
      {
        delete ptr;
      });

    // Create proxy guard that performs RAII.  The custom deleter lambda
    // captures the managed pointer by value, ensuring that the ticker
    // remains alive throughout the custom deleter call.
    return proxy_guard<ticker>(
      managed.get(), // Unmanaged
      [](ticker* ptr)        { ptr->start(); },
      [managed](ticker* ptr) { ptr->stop();  });
  }

  unsigned int count()
  {
    return count_;
  }

private:

  ticker(boost::asio::io_service& io_service)
    : io_service_(io_service),
      timer_(io_service),
      stopped_(false),
      count_(0)
  {
    std::cout << "ticker()" << std::endl;
  }

  ~ticker()
  {
    std::cout << "~ticker()" << std::endl;
  }
  
  static void destroy(ticker* ptr) { delete ptr; }

  /// @brief Start asynchronous loop between arm() and handle_wait().
  void start()
  {
    std::cout << "ticker::start()" << std::endl;
    arm();
  }

  /// @brief Cancel outstanding operations and set internal
  ///        state to stop asynchronous loops.
  void stop()
  {
    std::cout << "ticker::stop()" << std::endl;
    stopped_ = true;
    timer_.cancel();
  }

  /// @brief Arms the timer.
  void arm() 
  {
    std::cout << "ticker::arm()" << std::endl;
    timer_.expires_from_now(std::chrono::seconds(2));
    timer_.async_wait(
      boost::bind(&ticker::handle_wait, shared_from_this(),
                  boost::asio::placeholders::error));
  }

  /// @brief Invoked when timer expires.  
  void handle_wait(const boost::system::error_code& error)
  {
    std::cout << "ticker::handle_wait()\n" 
                 "  error: " << error.message() << "\n"
                 "  stopped: " << stopped_ << std::endl;

    // On error or being explicitly stopped, return early.  This
    // stops the asynchronous loop.
    if (error || stopped_) return;
    ++count_;
    arm();
  }

private:
  boost::asio::io_service&  io_service_;
  boost::asio::steady_timer timer_;
  bool                      stopped_;
  unsigned int              count_;
};

int main()
{
  boost::asio::io_service io_service;
  std::cout << "++ User handle being created. ++" << std::endl;
  auto ticker = ticker::create(io_service);
  while (!io_service.stopped())
  {
    io_service.poll();

    if (ticker)
    {
      const auto count = ticker->count();
      std::cout << "count is: " << count << std::endl;
      if (count == 1)
      {
        std::cout << "-- User handle being released. --" << std::endl;
        // This reset does not immediately force ticker to be destroyed.
        // Rather, it forces state to change, and ticker's internal
        // asynchronous call chain will stop generating more work, causing
        // shared_from_this() handles to reach 0.
        ticker.reset();
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));    
  }
}
