// See source code at: https://github.com/KjellKod/Concurrent




/** SHARED_QUEUE_hpp
* ==========================================================================
* 2010 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
* ============================================================================
*
* Example of a normal std::queue protected by a mutex for operations,
* making it safe for thread communication, using std::mutex from C++0x with
* the help from the std::thread library from JustSoftwareSolutions
* ref: http://www.stdthread.co.uk/doc/headers/mutex.html
*
* This exampel  was totally inspired by Anthony Williams lock-based data structures in
* Ref: "C++ Concurrency In Action" http://www.manning.com/williams */

// #pragma once

#include <queue>
#include <mutex>
#include <exception>
#include <condition_variable>

/** Multiple producer, multiple consumer thread safe queue
* Since 'return by reference' is used this queue won't throw */
template<typename T>
class shared_queue
{
  std::queue<T> queue_;
  mutable std::mutex m_;
  std::condition_variable data_cond_;

  shared_queue& operator=(const shared_queue&) = delete;
  shared_queue(const shared_queue& other) = delete;

public:
  shared_queue(){}

  void push(T item){
    {  
      std::lock_guard<std::mutex> lock(m_);
      queue_.push(std::move(item));
    }
    data_cond_.notify_one();
  }

  /// \return immediately, with true if successful retrieval
  bool try_and_pop(T& popped_item){
    std::lock_guard<std::mutex> lock(m_);
    if(queue_.empty()){
      return false;
    }
    popped_item=std::move(queue_.front());
    queue_.pop();
    return true;
  }

  /// Try to retrieve, if no items, wait till an item is available and try again
  void wait_and_pop(T& popped_item){
    std::unique_lock<std::mutex> lock(m_); 
    while(queue_.empty())
    { 
       data_cond_.wait(lock);
       //  This 'while' loop is equal to
       //  data_cond_.wait(lock, [](bool result){return !queue_.empty();});
    }
    popped_item=std::move(queue_.front());
    queue_.pop();
  }

  bool empty() const{
    std::lock_guard<std::mutex> lock(m_);
    return queue_.empty();
  }

  unsigned size() const{
    std::lock_guard<std::mutex> lock(m_);
    return queue_.size();
  }
};




// CONCURRENT_H
//#pragma once
// From a Herb Sutter Channel 9 presentation http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Herb-Sutter-Concurrency-and-Parallelism
// concurrent can wrap ANY object
// All access to the concurrent is done though a lambda. 
// All access call to the concurrent is done asynchronously but they are executed in FIFO order
// 
// At scope exit all queued jobs has to finish before the concurrent goes out of scope

//#include <shared_queue.hpp>   see above
#include <thread>
#include <future>
#include <functional>

namespace concurrent_helper {
   typedef std::function<void() > Callback;

   template<typename Fut, typename F, typename T>
   void set_value(std::promise<Fut>& p, F& f, T& t) {
      p.set_value(f(t));
   }

   // helper for setting promise/exception for promise of void
   template<typename F, typename T>
   void set_value(std::promise<void>& p, F& f, T& t) {
      f(t);
      p.set_value();
   }
} // namespace concurrent


/// Basically a light weight active object. www.kjellkod.cc/active-object-with-cpp0x#TOC-Active-Object-the-C-11-way
/// all input happens in the background. At shutdown it exits only after all 
/// queued requests are handled.
template <class T> class concurrent {
   mutable T _worker;
   mutable shared_queue<concurrent_helper::Callback> _q;
   bool _done; // not atomic since only the bg thread is touching it
   std::thread _thd;

   void run() const {
      concurrent_helper::Callback call;
      while (!_done) { 
         _q.wait_and_pop(call);
         call();
      }
   }

public:
   template<typename ... Args>
   concurrent(Args&&... args)
   : _worker(std::forward<Args>(args)...)
   , _done(false)
   , _thd([ = ]{concurrent_helper::Callback call;
      while (!_done) {  _q.wait_and_pop(call);  call();
      }}) {
   }

   ~concurrent() {
      _q.push([ = ]{_done = true;});
      _thd.join();
   }


   template<typename F>
   auto operator()(F f) const -> std::future<decltype(f(_worker))> {
      auto p = std::make_shared < std::promise < decltype(f(_worker)) >> ();
      auto future_result = p->get_future();
      _q.push([ = ]{
         try { concurrent_helper::set_value(*p, f, _worker); } catch (...) {
               p->set_exception(std::current_exception()); }
      });
      return future_result;
   }
};



// MAIN.CPP
//#include "concurrent.hpp"  // see above
#include <string>
#include <memory>
#include <chrono>
#include <iostream>
#include <cassert>
   // Verify concurrent runs,. "no" delay for the caller. 
   struct DelayedCaller {
      void DoDelayedCall() {
         std::this_thread::sleep_for(std::chrono::seconds(1));
      }
   };
   
struct Animal { virtual void sound() = 0; };
struct Dog : public Animal { void sound() override { std::cout << "Wof Wof" << std::endl; } };   
struct Cat : public Animal { void sound() override { std::cout << "Miauu Miauu" << std::endl; } };

int main() {
    // TEST 1 will take 10 seconds
    typedef std::chrono::steady_clock clock;
    auto start = clock::now();
    {
      concurrent<DelayedCaller> snail;
      for (size_t call = 0; call < 10; ++call) {
         snail([](DelayedCaller & slowRunner) { slowRunner.DoDelayedCall(); });
      }
      assert(std::chrono::duration_cast<std::chrono::seconds>(clock::now() - start).count() <= 1);
   } // at destruction all 1 second calls will be executed before we quit
   assert(std::chrono::duration_cast<std::chrono::seconds>(clock::now() - start).count() >= 10);
   
   
   // TEST 2 "un-copyable" wrapped objects
   typedef std::unique_ptr<Animal> RaiiAnimal;
   concurrent<RaiiAnimal> animal1 {new Dog};
   concurrent<RaiiAnimal> animal2 {new Cat};
   
   auto make_sound = []( RaiiAnimal& animal ) { animal->sound(); };
   animal1(make_sound);   
   animal2(make_sound);   
}




