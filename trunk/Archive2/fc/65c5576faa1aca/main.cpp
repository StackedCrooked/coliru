#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <cmath>

using namespace std;

class Ant {
private:
    int steps;
    vector<int> nodes;
public:
    Ant():steps(0) {};
    bool canMove() {
        return steps < 1000000;
    }
    void move() {
        nodes.push_back(rand() % 100);
        ++steps;
    }
};
    
class ThreadPool {
private:
    mutex m;
    condition_variable cv;
    bool joining;
    bool joined;
    bool syncing;
    bool synced;
    queue<shared_ptr<Ant> > jobs;
    vector<thread> threads;

    void run();
public:
    ThreadPool(uint8_t size);
    void enqueue(shared_ptr<Ant> ant);
    void sync();
    void join();
    void resume();
};

void ThreadPool::run() {
    unique_lock<mutex> lock(m, defer_lock);
    while (!joining) {
        while (!synced) {
            lock.lock();
            while (jobs.empty()) {
                cv.wait(lock);
            }
            shared_ptr<Ant> antPtr = jobs.front();
            jobs.pop();
            lock.unlock();
            cv.notify_one();

            while (antPtr->canMove()) {
                antPtr->move();
            }
        }
        cv.wait(lock);
    }
}

ThreadPool::ThreadPool(uint8_t size) : joining(false),
    joined(false), syncing(false), synced(false) {
    for (uint8_t i = 0; i < size; ++i) {
        threads.push_back(thread([this] () {
            run();
        }));
    }
}

void ThreadPool::enqueue(shared_ptr<Ant> ant) {
    if (syncing) {
        throw runtime_error("Cannot enqueue while syncing");
    }
    if (joined) {
        throw runtime_error("All threads are joined");
    }
    jobs.push(ant);
    cv.notify_one();
}

void ThreadPool::sync() {
    if (joined) {
        throw runtime_error("All threads are joined");
    }
    unique_lock<mutex> lock(m);
    syncing = true;
    while (!jobs.empty()) {
        cv.wait(lock);
    }
    synced = true;
    lock.unlock();
    cv.notify_all();
}

void ThreadPool::resume() {
    if (joined) {
        throw runtime_error("All threads are joined");
    }
    syncing = false;
    synced = false;
    cv.notify_all();
}

void ThreadPool::join() {
    sync();
    joining = true;
    cv.notify_all();
    for (auto& t : threads) {
        t.join();
    }
    joined = true;
}


int main()
{
    vector<shared_ptr<Ant> > antPtrs;
    for (int i = 0; i < 10; ++i) {
        antPtrs.push_back(make_shared<Ant>());
    }
    ThreadPool pool(2);
    
    for (auto& antPtr : antPtrs) {
        pool.enqueue(antPtr);
    }
}
