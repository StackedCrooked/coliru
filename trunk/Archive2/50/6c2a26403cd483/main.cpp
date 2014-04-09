#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <functional>
#include <boost/lockfree/queue.hpp>
#include <array>



template <int NN> using guardedArray =  std::array<std::pair<std::atomic<bool>,std::function<void()>>, NN> ;
using std::cout ; using std::cin; using std::endl;
using std::mutex; using std::atomic;
using std::array; using std::function;

template <typename T> using lockfreequeue = boost::lockfree::queue<T,boost::lockfree::capacity<1000>>;




mutex mm;

class Functor{
    int myNN;
public:
    Functor(int nn):myNN(nn){};
    Functor(std::function<void()> ff) : myff(ff){};
    std::function<void()> myff;
    Functor(const Functor&) = delete;
    Functor operator=(const Functor&) = delete;
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
	

	
	}while(compare_exchange_weak(&myGuardedArray[kk].second,&empty,true));
	myGuardedArray[kk].second = ff;
	
    };
    std::thread garbageCollectorThread;
    


};

void main(){}