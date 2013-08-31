#include <future>
#include <queue>
#include <mutex>
#include <exception>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <ostream>
#include <memory>


namespace herb {
  typedef std::function<void() > Callback;

  /** Multiple producer, multiple consumer thread safe queue
   * Since 'return by reference' is used this queue won't throw */
  template<typename T>
  class shared_queue {
    mutable std::queue<T> queue_;
    mutable std::mutex m_;
    mutable std::condition_variable data_cond_;

    shared_queue& operator=(const shared_queue&) = delete;
    shared_queue(const shared_queue& other) = delete;

  public:

    shared_queue() {
    }

    void push(T item) const {
      std::lock_guard<std::mutex> lock(m_);
      queue_.push(item);
      data_cond_.notify_one();
    }

    /// \return immediately, with true if successful retrieval

    bool try_and_pop(T& popped_item) const {
      std::lock_guard<std::mutex> lock(m_);
      if (queue_.empty()) {
        return false;
      }
      popped_item = queue_.front();
      queue_.pop();
      return true;
    }

    /// Try to retrieve, if no items, wait till an item is available and try again

    void wait_and_pop(T& popped_item) const {
      std::unique_lock<std::mutex> lock(m_); // note: unique_lock is needed for std::condition_variable::wait
      while (queue_.empty()) { //                       The 'while' loop below is equal to
        data_cond_.wait(lock); //data_cond_.wait(lock, [](bool result){return !queue_.empty();});
      }
      popped_item = queue_.front();
      queue_.pop();
    }

    bool empty() const {
      std::lock_guard<std::mutex> lock(m_);
      return queue_.empty();
    }

    unsigned size() const {
      std::lock_guard<std::mutex> lock(m_);
      return queue_.size();
    }
  };




  // ===========================================
  // Concurrent class wrapper. All access to the wrapped
  //      object goes through the ()(Func) operator
  //      all "Func" are executed ON the wrapped object
  //      Example:
  //     concurrent<string> shared_string;
  //     shared_string([](string& str){ str.append("Hello");});
  
  // helper for setting promise/exception
  template<typename Fut, typename F, typename T>
  void set_value(std::promise<Fut>& p, F& f, T&t) {
    p.set_value(f(t));
  }

// helper for setting promise/exception for promise of void
  template<typename F, typename T>
  void set_value(std::promise<void>& p, F& f, T&t) {
    f(t);
    p.set_value();
  }

  // Basically a light weight active object.
  // all input happens in the background. At shutdown it exits only after all 
  // queued requests are handled.
  template <class T> class concurrent {
    mutable T t;
    mutable shared_queue<Callback> q;
    bool done = false;  // not atomic since only the bg thread is touching it
    std::thread thd;

    void run() const {
      Callback call;
      while (!done) {
        q.wait_and_pop(call);
        call();
      }
    }

  public:
    concurrent(T t_) 
    : t(t_), 
     thd([ = ]{Callback call; while (!done) { q.wait_and_pop(call); call();   }}) 
     { }

    ~concurrent() {
      q.push([ = ]{done = true;});
      thd.join();
    }


    template<typename F>
    auto operator()(F f) const -> std::future<decltype(f(t))> {
      auto p = std::make_shared < std::promise < decltype(f(t)) >> ();
      auto future_result = p->get_future();
      q.push([ = ]{
        try {
          set_value(*p, f, t); }        catch (...) {
          p->set_exception(std::current_exception()); }
      });
      return future_result;
    }
  };
} // namespace herb


#include <string>
#include <iostream>
using namespace std;

  int main() {
    herb::concurrent<ostream&> ccoutx{cout};
    auto call1 = [=](ostream& oss){ oss << "xx" << " " << "xx" << endl; };
    auto res_0 = ccoutx(call1);
    
    auto res_1 = ccoutx([ = ](ostream & oss){oss << "yy" << " " << "yy" << endl;});
    res_1.wait();
    res_0.wait();
    
    // lets spice up a bit. 
    {
    herb::concurrent<ostream&> ccout{cout}; // OBSERVE:  you must wait till its destructor to be sure all asyncs have been processed
    std::vector<future<void>>  future_results;
    for(int i = 0; i < 100; ++i) {
       auto call1 = [=](ostream& oss){ std::this_thread::sleep_for(std::chrono::microseconds(1));  cout << i << " "<< endl; };
       auto async_result = std::async(std::launch::async,      [=, &ccout]{ccout(call1);});
       future_results.push_back(std::move(async_result));
    }
    
    for(auto& fut: future_results) fut.wait();
    future_results.clear();
    } // scope exit all asyn joins

    cout << "DOING IT THE UNSAFE WAY" << endl;
    cout << "===================================================" << endl;
    std::vector<future<void>>  future_results;
    for(int i = 0; i < 100; ++i) {
       auto call1 = [=](int VALUE){ std::this_thread::sleep_for(std::chrono::microseconds(1));  cout << VALUE << " " << endl; };
       auto async_result = std::async(std::launch::async, [=]{call1(i);});
       future_results.push_back(std::move(async_result));
    }
    for(auto& fut: future_results) fut.wait();
    future_results.clear();
    
    } // scope exit all asyn joins

  



   





