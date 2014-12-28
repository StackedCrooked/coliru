#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

class barrier {
    const unsigned int threadCount;
	std::atomic<unsigned int>threadsWaiting;
	bool isNotWaiting;
	std::condition_variable waitVariable;
	std::mutex mutex;
public:
	barrier(unsigned int n) : threadCount(n) {
		threadsWaiting = 0;
		isNotWaiting = false;
	}
	barrier(const barrier &) = delete;
	void wait() {
		if (threadsWaiting.fetch_add(1) >= threadCount - 1) {
			isNotWaiting = true;
			waitVariable.notify_all();
			threadsWaiting.store(0);
		} else {
			std::unique_lock<std::mutex> lock(mutex);

            //1. Подставлено тело waitVariable.wait(lock, predicate)            
			while (![&]{ return isNotWaiting; }()){
                 //2. Добавлена задержка на некотрое время (например, в этот момент вмешался системный планировщик)
                 //Можно использовать любую задержку по выбору:
                 
			    //std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 180));                 
                for ( volatile int i = 0; i < 1000000; i++) {}   
                
                //3. Наблюдаем в консоли, что один из потоков так никогда и не просыпается
				waitVariable.wait(lock);
			}
            
            //Альтернативный вариант (оставляем версию с предикатом, задержку вставляем после чтения переменной но перед возвратом)
            /*
            waitVariable.wait(lock, [&](){
    			bool notWaiting = *(volatile bool*)&isNotWaiting;
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 180));
				return notWaiting;
			});
            */
		}
	}
};


barrier *myBarrier;

class Thread {
private:
	std::thread* cppthread;
	static void threadFunction(Thread* arg) {
		arg->run();
	}
public:
	Thread() {}
	Thread(const Thread&) = delete;
	virtual ~Thread() { delete cppthread; }
	virtual void run() = 0;
	void start() {
		cppthread = new std::thread(Thread::threadFunction, this);
	}
	void wait() {
		cppthread->join();
	}
};

class BarrierDemo : public Thread {
	int id;
public:
	BarrierDemo(int i) {
		id = i;
	}
	void run() {
		std::cout << "Thread " << id << "runs before barrier" << std::endl;
		myBarrier->wait();
		std::cout << "Thread " << id << "runs after barrier" << std::endl;
	}
};

int main() {
	// your code goes here
	int threads = 5;
    
	myBarrier = new barrier(threads);

	BarrierDemo* bardemos = static_cast<BarrierDemo*>(::operator new(sizeof(BarrierDemo)*threads));

	for (int i = 0; i < threads; i++) {
		new (&bardemos[i])BarrierDemo(i);
		bardemos[i].start();
	}
	for (int i = 0; i < threads; i++) {
		bardemos[i].wait();
	}


	::operator delete(bardemos);
	delete myBarrier;
	return 0;
}