#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <functional>
#include <boost/lockfree/queue.hpp>
#include <array>



// #include "lockfreequeue.h"


using std::cout ; using std::cin; using std::endl;
using std::mutex; using std::atomic;
using std::array; using std::function;

template <int NN> using guardedArray =  std::array<std::pair<std::atomic<bool>,std::function<void()>>, NN> ;

template <typename T> using lockfreequeue = boost::lockfree::queue<T,boost::lockfree::capacity<1000>>;




mutex mm;

class Functor{
    int myNN;
public:
    Functor(int nn):myNN(nn){};
    Functor(std::function<void()> ff) : myff(ff){};
    std::function<void()> myff;
    Functor(const Functor&) = default;
    Functor operator=(const Functor&) ;
    ~Functor() = default;
    void operator()(){
    myff();

    }
};



template <int NN > class GuardedArray{


    guardedArray<NN> myGuardedArray; 
public:
    int insertObject(std::function<void()> ff){
	int kk ;
	bool empty;

	do{
	kk = rand () % NN;
	empty = myGuardedArray[kk].first;
	cout << "spining ... " << endl;

	
	}while(!(std::atomic_compare_exchange_weak(&myGuardedArray[kk].first,&empty,true)));
	myGuardedArray[kk].second = ff;
	return kk;
    };
    std::function<void()> getIndex(int ii){return myGuardedArray[ii].second  ; };
    std::thread garbageCollectorThread;
    


};

template <int NN > class ThreadPool{

private:
    std::thread tt[NN];
    GuardedArray<1000> myGA;
    bool endFlag;
public:
    ThreadPool():endFlag(false){

	for(int ii = 0 ; ii < NN ; ++ii){	    
	    std::thread localThread(&ThreadPool<NN>:: threadLoop, this);
	    tt[ii].swap(localThread);

	}

    };
    void bookTask(std::function<void()> ff){
	int ii = myGA.insertObject(ff);
	mySync.push(ii);
    };

    bool demandedAccess[NN];
    int waitingProcess;
    ~ThreadPool() {endFlag = true; for (int ii = 0 ; ii < 10 ; ii++  ){  tt[ii].join();}   };
    int myWrapper();
    bool execute(void *());
    void threadLoop();
    lockfreequeue<int> mySync;

};

template <int NN> void ThreadPool<NN>::threadLoop(){
    std::thread::id kk  = std::this_thread::get_id();
    std::function<void()> fun ; 
    int ff;
    while(!endFlag){

	if(!mySync.empty()){
	    
	    bool result = mySync.pop(ff);
	    if(result){
		fun = myGA.getIndex(ff);	    
		fun();
	    }
	}
    }
}

template <int NN> bool ThreadPool<NN>::execute(void *ff()){


    

    return 1;
}



int main(int argc, char** argv){
  
    ThreadPool<10> tp;
    Functor ff(( [](){ cout <<"a kuku  "<<endl;  }));
    tp.bookTask(ff);
    std::this_thread::sleep_for(std::chrono::seconds(20));

    return 0 ; 
}
