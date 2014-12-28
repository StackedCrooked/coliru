#include <queue>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <boost/thread/condition_variable.hpp> 
#ifndef SYNCHRONIZEDQUEUE_DEF
#define SYNCHRONIZEDQUEUE_DEF 
template<class T>
class SynchronizedQueue
{
private:
 ///The queue itself
 std::queue<T> sQueue;
 ///A mutex object to control access to the std::queue
 boost::mutex io_mutex_;
 ///A variable condition to make threads wait on specified condition values
 public:
 //default Constructor
SynchronizedQueue();
 //destructor
 virtual ~SynchronizedQueue();
 void push(T& element);
 bool empty();
 bool pop(T& element);
 unsigned int sizeOfQueue();
 void waitAndPop(T& element);
 std::string toString();
  
};
template<class T>
//default constructor
SynchronizedQueue<T>::SynchronizedQueue(){}
template<class T>
//default desconstructor
SynchronizedQueue<T>::~SynchronizedQueue(){}
template<class T>
void SynchronizedQueue<T>::push(T element)
{
    //try to lock the mutex
    boost::mutex::scoped_lock lock(io_mutex_);
    //insert the element in the FIFO queue
    SynchronizedQueue::sQueue.push(element);
    //Now we need to unlock the mutex otherwise waiting threads will not be able to wake and lock the
    //mutex by time before push is locking again
    lock.unlock();
    //notifiy waiting thread they can pop/push now
    waitCondition.notify_one();
}

template<class T>
bool SynchronizedQueue<T>::empty()
{
    //try to lock the mutex
    boost::mutex::scoped_lock lock(io_mutex_);
    return SynchronizedQueue::sQueue.empty();
}
template<class T>
bool SynchronizedQueue<T>::pop(T& element)
{
 
     //try to lock the mutex
     boost::mutex::scoped_lock lock(io_mutex_);
 
     //ask if the queue is empty
     if (SynchronizedQueue::sQueue.empty())
     {
 return false;
     }
 
     //get the last inserted element
     element = SynchronizedQueue::sQueue.front();
     //remove the last inserted element, since we have a copy in element
     SynchronizedQueue::sQueue.pop();
 
     //no need to unlock the mutex, it will get unlocked when the function ends
     return true;

};
template<class T>
void SynchronizedQueue<T>::waitAndPop(T& element)
{
 
    //try to lock the mutex
    boost::mutex::scoped_lock lock(io_mutex_);
    //while the queue is empty, make the thread that runs this wait
    while(SynchronizedQueue::sQueue.empty())
    {
 waitCondition.wait(lock);
    }
 
    //when the condition variable is unlocked, popped the element
    element = SynchronizedQueue::sQueue.front();
 
    //pop the element
    sQueue.pop();
 
};
template<class T>
unsigned int SynchronizedQueue<T>::sizeOfQueue()
{
 //try to lock the mutex
 boost::mutex::scoped_lock lock(io_mutex_);
 return SynchronizedQueue::sQueue.size();
 
};
template<class T>
std::string SynchronizedQueue<T>::toString()
{
    std::stringstream os;
 
    //make a copy of the class queue, so we dont care about mangling with threads
    std::queue<T> copy = SynchronizedQueue::sQueue;
 
    //check the queue is not empty
    if (!copy.empty())
    {
     int counter = 0; 
     os << "Elements in the Synchronized queue are as follows:" << std::endl;
     os << "**************************************************" << std::endl;
 
     while (!copy.empty())
 {
      //get the first element in the queue
  boost::any object = copy.front();
  std::string b = "Element at position " + boost::lexical_cast<std::string>(counter) + " is: ";
  b.append("[");
  b.append(object.type().name());
  b.append("]\n");
      os << b;
      //remove the element in the queue
      copy.pop();
 }
     return os.str();
    }
    else
    {
     os << "Queue is empty";
     return os.str();
    }
}