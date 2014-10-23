/**
*  @file SynchronizedQueue.h
*
*  @brief Header for the Template class SynchronizedQueue.
*
*  Provides a thread-safe blocking queue wrapper based on the std::queue
*
*  @date 03/28/2011
*
*  @author Alejandro Villamarin
*/


#include <queue>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <boost/thread/condition_variable.hpp>


#ifndef SYNCHRONIZEDQUEUE_DEF
#define SYNCHRONIZEDQUEUE_DEF

/**
*  @class SynchronizedQueue
*
*  @brief Provides a thread-safe blocking queue wrapper based on the std::queue
*
*  @date 20/10/2010
*
*  @author Alejandro Villamarin
*/
    template<class T>
	class SynchronizedQueue
	{

	private:
		///The queue itself
		std::queue<T> sQueue;
		///A mutex object to control access to the std::queue
		boost::mutex io_mutex_;
		///A variable condition to make threads wait on specified condition values
		boost::condition_variable waitCondition;

	public:
		//default Constructor
		SynchronizedQueue();
		//destructor
		virtual ~SynchronizedQueue();
		void push(T element);
		bool empty();
		bool pop(T&);
		unsigned int sizeOfQueue();
		void waitAndPop(T&);
		std::string toString();

		
	};


	/**
	*  Constructor
    *
	*  @return void
	*
	 */
	template<class T>
		//default constructor
		SynchronizedQueue<T>::SynchronizedQueue(){}


	/**
	*  Destructor
    *
	*  @return void
	*
	 */
	template<class T>
		//default destructor
		SynchronizedQueue<T>::~SynchronizedQueue(){}




	/**
	*  Adds an element to the queue in a blocking mode (thread-safe)
    *
	*  @return void
	*
	 */
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


	/**
	*  Checks if the queue is empty or not
    *
	*  @return TRUE if the queue is not empty
	*
	 */
	template<class T>
	bool SynchronizedQueue<T>::empty()
	{
		//try to lock the mutex
		boost::mutex::scoped_lock lock(io_mutex_);
	    return SynchronizedQueue::sQueue.empty();
	}


	/**
	*  It tries to pop an element from the queue but does not keep waiting if the queue
	*  is empty
    *
    *  @param A reference to object T to hold the popped element
	*  @return void
	*
	 */
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

	}


	/**
	*  Return the size of the queue
    *
	*  @return number of elements in the queue
	*
	 */
	template<class T>
	unsigned int SynchronizedQueue<T>::sizeOfQueue()
	{
		//try to lock the mutex
		boost::mutex::scoped_lock lock(io_mutex_);
		return SynchronizedQueue::sQueue.size();

	}




	/**
	*  Keeps any thread waiting if the queue is empty and when is not
	*  it returns the element at the front of the queue
	*
	*  @param A reference to object T to hold the popped element
	*  @return A reference to an object of type T in the queue
	*
	 */
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

	}


	/**
	*  Iterates throught the queue elements and returns a string representing them
	*
	*  @return string the textual representation of the queue
	*
	 */
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




#endif

#include <boost/serialization/access.hpp>



class gps_position
{
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & degrees;
            ar & minutes;
            ar & seconds;
        }
    public:
    int degrees;
    int minutes;
    float seconds;

    gps_position() {}
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}
};

char *SHARED_MEMORY_NAME = "MySharedMemory";
char *SHARED_QUEUE_NAME  =  "MyQueue";
typedef SynchronizedQueue<gps_position> MySynchronisedQueue;

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
using boost::interprocess::shared_memory_object;
using boost::interprocess::managed_shared_memory;
using boost::interprocess::create_only;
using boost::interprocess::open_only;

void producer() {
    // Remove shared memory if it was created before
    shared_memory_object::remove(SHARED_MEMORY_NAME);
    // Create a new segment with given name and size
    managed_shared_memory mysegment(create_only,SHARED_MEMORY_NAME, 65536);
    MySynchronisedQueue *myQueue = mysegment.construct<MySynchronisedQueue>(SHARED_QUEUE_NAME)();
    //Insert data in the queue
    for(int i = 0; i < 100; ++i)  {
        gps_position position(i, 2, 3);
        myQueue->push(position);
    }
    // Start 1 process (for testing for now)
    STARTUPINFO info1={sizeof(info1)};
    PROCESS_INFORMATION processInfo1;
    ZeroMemory(&info1, sizeof(info1));
    info1.cb = sizeof info1 ; //Only compulsory field
    ZeroMemory(&processInfo1, sizeof(processInfo1));
    // Launch child process
    LPTSTR szCmdline = _tcsdup(TEXT("ClientTest.exe"));
    CreateProcess(NULL, szCmdline, NULL, NULL, TRUE, 0, NULL, NULL, &info1, &processInfo1);
    // Wait a little bit ( 5 seconds) for the started client process to load
    WaitForSingleObject(processInfo1.hProcess, 5000);

    /* THIS TESTING CODE WORK HERE AT PARENT PROCESS BUT NOT IN CLIENT PROCESS
    // Open the managed segment memory
    managed_shared_memory openedSegment(open_only, SHARED_MEMORY_NAME);
    //Find the synchronized queue using it's name
    MySynchronisedQueue *openedQueue = openedSegment.find<MySynchronisedQueue>(SHARED_QUEUE_NAME).first;
    gps_position position;
    while (true) {
    if (myQueue->pop(position)) {
    std::cout << "Degrees= " << position.degrees << " Minutes= " << position.minutes << " Seconds= " << position.seconds;
    std::cout << "\n";
    }
    else
    break;
    }*/


    // Wait until the queue is empty: has been processed by client(s)
    while(myQueue->sizeOfQueue() > 0) continue;

    // Close process and thread handles. 
    CloseHandle( processInfo1.hThread );
}

void consumer() {
    //Open the managed segment memory
    managed_shared_memory segment(open_only, SHARED_MEMORY_NAME);
    //Find the vector using it's name
    MySynchronisedQueue *myQueue = segment.find<MySynchronisedQueue>(SHARED_QUEUE_NAME).first;
    gps_position position;
    // Pop each position until the queue become empty and output its values
    while (true)
    {
        if (myQueue->pop(position)) { // CRASH HERE
            std::cout << "Degrees= " << position.degrees << " Minutes= " << position.minutes << " Seconds= " << position.seconds;
            std::cout << "\n";
        }
        else
            break;
    } 
}

int main()
{
    producer();
    consumer();
}
