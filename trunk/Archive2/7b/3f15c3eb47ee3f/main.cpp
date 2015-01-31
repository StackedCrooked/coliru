#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>
#include <atomic>
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

void printThreadAffinity(){
  pthread_t thread = pthread_self();
  cpu_set_t cpuset;
  int st = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
  if (st != 0)
    printf("pthread_getaffinity_np error\n");

  printf("Set returned by pthread_getaffinity_np() contained:\n");
  for (int j = 0; j < CPU_SETSIZE; j++)
    if (CPU_ISSET(j, &cpuset))
      printf("    CPU %d\n", j);
}

struct Log{
public:
  Log(std::string const & logFileName, int32_t coreNumber, int32_t queueSize, std::vector<int32_t> const & pushCores)
    : logFileName(logFileName), coreNumber(coreNumber), lock(ATOMIC_FLAG_INIT)
  {
    //    this->fp = std::fopen(logFileName.c_str(),"w");                                                                              
    this->fp = stderr;
    std::atomic_store_explicit(&this->flag,true,std::memory_order_release);
    this->thrd.reset(new boost::thread(&Log::pop,this));
    this->q.reset(new boost::lockfree::spsc_queue<std::string>(queueSize));
    setThreadAffinity(this->thrd.get(),coreNumber);

    //                                                                                                                                 
    this->io_service.reset(new boost::asio::io_service);
    this->work.reset(new boost::asio::io_service::work(*this->io_service));
    for (unsigned i = 0; i < pushCores.size(); ++i){
      boost::thread * t_thread = this->thread_pool.create_thread(boost::bind(&boost::asio::io_service::run,this->io_service.get()));
      setThreadAffinity(t_thread,pushCores[i]);
    }
  }

inline __attribute__((always_inline)) void pop(){
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
  }

template <typename T>
  inline __attribute__((always_inline)) std::string stringer(T const & t){
    return boost::lexical_cast<std::string>(t);
  }

  template<typename T, typename ... Args>
  inline __attribute__((always_inline))
  std::string stringer(T const & t, Args const & ... args){
    return stringer(t) + stringer(args...);
  }

  template<typename T, typename ... Args>
  inline __attribute__((always_inline)) void enqueue(T & t, Args & ... args){
    auto f = boost::bind(&Log::stringer<T &, Args & ...>,this,boost::ref(t),boost::forward<Args>(args)...);
    //    std::cerr << f() << std::endl;                                                                                               
    //this->io_service->post(f());                                                                                                     
    //    std::fprintf(stderr,"%s\n",f().c_str());                                                                                     
  }

 inline __attribute__((always_inline)) void push(std::string const & s){
    while (std::atomic_flag_test_and_set_explicit(&this->lock,std::memory_order_acquire));
    while (!this->q->push(s));
    std::atomic_flag_clear_explicit(&this->lock,std::memory_order_release);
  }

~Log(){
    this->io_service->stop();
    this->thread_pool.join_all();

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
  boost::scoped_ptr<boost::asio::io_service> io_service;
  boost::scoped_ptr<boost::asio::io_service::work> work;
  boost::thread_group thread_pool;
};


int main(){

  std::vector<int32_t> pushCores;
  for (int i = 0; i < 10; ++i){
    pushCores.push_back(i);
    pushCores.push_back(i);
  }
  //  pushCores.push_back(16); pushCores.push_back(17), pushCores.push_back(18), pushCores.push_back(19);                              
  Log l("/tmp/junk.log",15,1024,pushCores);
  struct timeval ts_1, ts_2;
  gettimeofday(&ts_1,NULL);
  for (int64_t i = 0; i < 1; ++i){
    l.enqueue("hello"," world");
  }
  gettimeofday(&ts_2,NULL);
  std::fprintf(stderr,"%d microsec\n",(ts_2.tv_sec-ts_1.tv_sec)*1000000+(ts_2.tv_usec-ts_1.tv_usec));

  return 0;
}