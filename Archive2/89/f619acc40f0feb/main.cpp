#define _BLITZ_LOGGER_H_

#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>
#include <cstdatomic>
#include <boost/lockfree/spsc_queue.hpp>
#include <string>
#include <sstream>
#include <cstdio>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <boost/scoped_ptr.hpp>
#include <sys/time.h>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/move/utility.hpp>
#include "helpers.h"
#include <functional>
#include <tr1/functional>

namespace blitz{
  template<unsigned popResSize = 1024>
    struct BlitzLogger{
    public:
    BlitzLogger (std::string const & logFileName, int32_t const popCore, int32_t const pushCore, int32_t queueSize)
    : fp(std::fopen(logFileName.c_str(),"w")),flag(true),ctr(0),
      q(new boost::lockfree::spsc_queue<std::string>(queueSize)),
      pop_thread(new boost::thread(&BlitzLogger::pop,this)),
      io_service(new boost::asio::io_service),
      work(new boost::asio::io_service::work(*io_service)),
      push_thread(new boost::thread(boost::bind(&boost::asio::io_service::run,this->io_service.get())))
      {
        helpers::setThreadAffinity(this->pop_thread.get(),popCore);
        helpers::setThreadAffinity(this->push_thread.get(),pushCore);
      }

      template<typename T, typename ... Args>
      inline __attribute__((always_inline))
      void enqueue(T const & t, Args const & ... args){
        std::atomic_fetch_add_explicit(&this->ctr,1,std::memory_order_release);
        this->concatenate(t,args ...);
      }

  ~BlitzLogger(){
        while (std::atomic_load_explicit(&this->ctr,std::memory_order_acquire));
        this->io_service->stop();
        this->flag = false;
        this->pop_thread->join();
        std::fflush(this->fp);
        if (this->fp != stdout && this->fp != stderr) std::fclose(this->fp);
        this->fp = NULL;
      }

 private:
      BlitzLogger(){}
      FILE * fp;
      std::atomic<bool> flag;
      std::atomic<int> ctr;
      boost::scoped_ptr<boost::lockfree::spsc_queue<std::string> > q;
      boost::scoped_ptr<boost::thread> pop_thread;
      boost::scoped_ptr<boost::asio::io_service> io_service;
      boost::scoped_ptr<boost::asio::io_service::work> work;
      boost::scoped_ptr<boost::thread> push_thread;

 inline __attribute__((always_inline))
      void pop(){
        std::string s;
        s.reserve(popResSize);
        struct timeval ts;
        while (this->flag){
          while (this->q->pop(s)){
            gettimeofday(&ts,NULL);
            std::fprintf(this->fp,"%d.%06d %s",ts.tv_sec,ts.tv_usec,s.c_str());
          }
          std::fflush(this->fp);
        }
        while (this->q->pop(s)){
          gettimeofday(&ts,NULL);
          std::fprintf(this->fp,"%d.%06d %s",ts.tv_sec,ts.tv_usec,s.c_str());
        }
      }

      template <typename T>
      inline __attribute__((always_inline))
      std::string stringer(T const & t){
        return boost::lexical_cast<std::string>(t);
      }

 template<typename T, typename ... Args>
        inline __attribute__((always_inline))
        std::string stringer(T const & t, Args const & ... args){
        return stringer(t) + stringer(args...);
      }

      template <typename T, typename ... Args>
        inline __attribute__((always_inline))
        void concatenate(T t, Args ... args){
        this->io_service->post(std::tr1::bind(&BlitzLogger::push,this,std::tr1::bind(&BlitzLogger::stringer<T const &,
                                                                                     Args const & ...>,
                                                                                     this,std::tr1::ref(t),
                                                                                     std::tr1::ref(args) ...)));
      }



  inline __attribute__((always_inline))
      void push(std::string const & s){
        while (!this->q->push(s));
        std::atomic_fetch_sub_explicit(&this->ctr,1,std::memory_order_release);
      }

    };
};



int main(){

 BlitzLogger<> l("/tmp/junk.log",15,15,1024);
    struct timeval ts_1, ts_2;

 gettimeofday(&ts_1,NULL);
 
    // burn in
 for (int64_t i = 0; i < 10; ++i){
   l.enqueue("hello",1,2,3,5.36," world\n");
  }
  

  gettimeofday(&ts_1,NULL);
  
   {
    for (int i = 0; i < 333333; ++i){
      //      l.enqueue("hello",42,32,45);                                                                                             
      l.enqueue("check this out", 2, 4.3, "junk it\n");
      l.enqueue("trade @ ", 100," for ", 42000,"sadadahares for instrument ", 4.3, "junk it\n",42);
      l.enqueue("check thasdadis out", 2, 4.3, "junasdk it","trade @ ", 100," for ", 42000,
                "check adadathasdadis out", 2, 4.3, "juadadadnasdk it","tradeasd @ ", 100," for ", 420930,
                "check thasdadis out", 2, 4.3, "junasdk it","trade @ ", 100," for ", 42000);
    }
  }

 gettimeofday(&ts_2,NULL);
  std::fprintf(stderr,"%d microsec\n",(ts_2.tv_sec-ts_1.tv_sec)*1000000+(ts_2.tv_usec-ts_1.tv_usec));







