#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <functional>

using std::cout ; using std::cin; using std::endl;
using std::mutex; using std::atomic;


mutex mm;

class Functor{
    int myNN;
public:
    Functor(int nn):myNN(nn){};
    ~Functor() = default;
    void operator()(){
    std::lock_guard<mutex> myGuard (mm);
	cout << "hello from the " << myNN << endl; 

    }



};


template<typename T> class SyncedQueue{
private:
    template <typename U> class Node{
	U value;
	Node<U> *prev;
    public:
	Node(U tt):value(tt),prev(nullptr){}
	Node():prev(nullptr){}
};



    std::atomic<Node<T>*> head;
    std::atomic<Node<T>*> tail;


public:
    SyncedQueue():head(nullptr),tail(nullptr){};
    SyncedQueue(T tt):head(new Node<T>(tt)),tail(head){};




    void push_back(T tt){
	Node<T> *newNode = new Node<T>(tt);
	if(tail!=nullptr){
	    tail->prev = newNode ;
	    tail = newNode->prev;
	}
	else{
	    head = tail = newNode;
	}


    }
    void pop_front(){
	if(head==nullptr)
	    return;
	else{
	    Node<T>* old_head = head;
	    head = head->prev;
	    delete old_head;

	    if(head==nullptr)
		tail = nullptr;	    
	}
    }
    T top(){

	return head->value;

    }



};


template <int NN > class ThreadPool{

private:
    std::thread tt[NN];

public:
    ThreadPool(){

	for(int ii = 0 ; ii < NN ; ++ii){	    
	    Functor myFF(ii);
	    std::thread localThread(myFF);
	    tt[ii].swap(localThread);
	    tt[ii].detach();
	    
	}

    };

    bool demandedAccess[NN];
    int waitingProcess;
    ~ThreadPool() = default;
    int myWrapper();
    bool execute(void *());
    void threadLoop();


};





template <int NN> void ThreadPool<NN>::threadLoop(){
    static std::thread::id kk  = std::this_thread::get_id();

    while(true){

	cout << "hello from the " << kk << endl; 


    }
}

template <int NN> bool ThreadPool<NN>::execute(void *ff()){


    


}



int main(int argc, char** argv){

  
  SyncedQueue<std::function<void ()>> myQueue;
  ThreadPool<10> tp;
  std::this_thread::sleep_for(std::chrono::seconds(20));

  return 0 ; 


}
