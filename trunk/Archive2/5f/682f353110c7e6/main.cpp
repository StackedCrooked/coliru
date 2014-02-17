#include <queue>
#include <iostream>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <condition_variable>

class Queue{
public:
    Queue() : m_isProgramStopped( false ) { }

    void push(int i){
        std::unique_lock<std::mutex> lock(m_mtx);
        m_q.push(i);
        m_cond.notify_one();
    }

    int pop(){
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [&](){ return !m_q.empty() || m_isProgramStopped; });

        if (m_isProgramStopped){
            throw std::runtime_error("Program stopped!");
        }

        int x = m_q.front();
        m_q.pop();

        std::cout << "Thread " << std::this_thread::get_id() << " popped " << x << "." << std::endl;
        return x;
    }

    void stop(){
        m_isProgramStopped = true;
        m_cond.notify_all();
    }

private:
    std::queue<int> m_q;
    std::mutex m_mtx;
    std::condition_variable m_cond;
    bool m_isProgramStopped;
};

class Producer{
public:
    Producer(Queue & q) : m_q( q ), m_counter(1) { }

    void produce(){
        for (int i = 0; i < 5; i++){
            m_q.push(m_counter++);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    void execute(){
        m_t = std::thread(&Producer::produce, this);
    }

    void join(){
        m_t.join();
    }

private:
    Queue & m_q;
    std::thread m_t;

    unsigned int m_counter;
};

class Consumer{
public:
    Consumer(Queue & q) : m_q (q) , m_takeCounter(0), m_isRunning(true)
    { }

    ~Consumer(){
        std::cout << "KILL CONSUMER! - TOOK: " << m_takeCounter << "." << std::endl;
    }

    void consume(){
        while (m_isRunning){
            try{
                m_q.pop();
                m_takeCounter++;
            }
            catch (std::exception const& e){
                std::cout << "Program was stopped while waiting." << std::endl;
            }
        }
    }

    void execute(){
        m_t = std::thread(&Consumer::consume, this);
    }

    void join(){
        m_t.join();
    }

    void stop(){
        m_isRunning = false;
    }

private:
    Queue & m_q;
    std::thread m_t;

    unsigned int m_takeCounter;
    bool m_isRunning;
};

int main(void){
    Queue q;

    Consumer cons(q);
    Producer prod(q);

    cons.execute();
    prod.execute();

    prod.join();

    cons.stop();
    q.stop();

    cons.join();

    std::cout << "END" << std::endl;

    return EXIT_SUCCESS;
}
