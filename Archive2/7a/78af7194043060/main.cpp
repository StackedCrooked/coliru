#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>
#include <cstdatomic>
#include <boost/lockfree/spsc_queue.hpp>
#include <string>
#include <cstdio>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <boost/scoped_ptr.hpp>
#include <sys/time.h>
#include <boost/lexical_cast.hpp>



void setThreadAffinity(boost::thread * const bt, int32_t const coreNumber){
  cpu_set_t cst;
  CPU_ZERO(&cst);
  CPU_SET(coreNumber,&cst);
  pthread_setaffinity_np(bt->native_handle(),sizeof(cst),&cst);
}

void setThreadAffinity(int32_t const coreNumber){
  cpu_set_t cst;
  CPU_ZERO(&cst);
  CPU_SET(coreNumber,&cst);
  sched_setaffinity(0,sizeof(cst),&cst);
}

struct Log{
public:
  Log(std::string const & logFileName, int32_t coreNumber, int32_t queueSize)
    : logFileName(logFileName), coreNumber(coreNumber), lock(ATOMIC_FLAG_INIT)
  {
    this->fp = std::fopen(logFileName.c_str(),"w");
    std::atomic_store_explicit(&this->flag,true,std::memory_order_release);
    this->thrd.reset(new boost::thread(&Log::pop,this));
    this->q.reset(new boost::lockfree::spsc_queue<std::string>(queueSize));
    setThreadAffinity(this->thrd.get(),coreNumber);
  }

  void pop(){
    //    setThreadAffinity(this->coreNumber);                                                                                         
    std::string s;
    s.reserve(1000);
    struct timeval ts;
    while (std::atomic_load_explicit(&this->flag,std::memory_order_acquire)){
      while (this->q->pop(s)){
        gettimeofday(&ts,NULL);
        std::fprintf(this->fp,"%d.%06d %s\n",ts.tv_sec,ts.tv_usec,s.c_str());
      }
      std::fflush(this->fp);
    }
    while (this->q->pop(s)){
      gettimeofday(&ts,NULL);
      std::fprintf(this->fp,"%d.%06d %s\n",ts.tv_sec,ts.tv_usec,s.c_str());
    }

void push(std::string const & s){
    while (std::atomic_flag_test_and_set_explicit(&this->lock,std::memory_order_acquire));
    while (!this->q->push(s));
    std::atomic_flag_clear_explicit(&this->lock,std::memory_order_release);
  }


  ~Log(){
    std::atomic_store_explicit(&this->flag,false,std::memory_order_release);
    this->thrd->join();
    std::fflush(this->fp);
    std::fclose(this->fp);
    this->fp = NULL;
  }

private:
  Log(){}
  std::string logFileName;
  int32_t coreNumber;
  boost::scoped_ptr<boost::lockfree::spsc_queue<std::string> > q;
  boost::scoped_ptr<boost::thread> thrd;
  std::atomic<bool> flag;
  std::atomic_flag lock;
  FILE * fp;
};


// this is the piece of code that achieves the best time -> about 2-3 microseconds for this single print on the server i use


int main(){

  Log l("/tmp/junk.log",15,1024);
  struct timeval ts_1, ts_2;
  gettimeofday(&ts_1,NULL);
  for (int64_t i = 0; i < 1; ++i){
    std::string s("let's log this long line");
    //    sleep(1);                                                                                                                    
    l.push(s);
  }
  gettimeofday(&ts_2,NULL);
  
  // below is the benchmark print
  std::fprintf(stderr,"%d microsec\n",(ts_2.tv_sec-ts_1.tv_sec)*1000000+(ts_2.tv_usec-ts_1.tv_usec));

  return 0;

}

