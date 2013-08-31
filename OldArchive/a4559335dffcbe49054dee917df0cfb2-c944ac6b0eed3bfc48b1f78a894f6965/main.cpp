#include <iostream>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

template<typename T> class threadsafe_queue
{
    private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    std::mutex head_mutex;   //when change the head lock it.
    std::unique_ptr<node> head;  
    std::mutex tail_mutex;   //when change the tail lock it.
    node* tail;
    std::condition_variable data_cond;

    node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    public:
    /* 
        create a dummy node
    */
    threadsafe_queue():
        head(new node),tail(head.get())
    {}

    std::shared_ptr<T> wait_and_pop()
    {
        auto predicate = [this]() -> bool {
            bool test = head.get() != get_tail();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return test;
        };
        std::unique_lock<std::mutex> head_lock(head_mutex);
        bool result = data_cond.wait_for(head_lock, std::chrono::seconds(10), predicate); //#1
        if (!result) {
            std::cout << "Timeout occurred and queue is empty!\n";
            std::terminate();
        }
        std::unique_ptr<node> old_head=std::move(head);
        head=std::move(old_head->next);
        return old_head->data;
    }

    void push(T new_value)
    {
        std::shared_ptr<T> new_data(
        std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->data=new_data;
            node* const new_tail=p.get();
            tail->next=std::move(p);
            tail=new_tail;
        }
        data_cond.notify_one();
    }
};

static threadsafe_queue<int> queue;

void producer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queue.push(42);
}

void consumer() {
    int val = *queue.wait_and_pop();
    std::cout << "Consumer: got " << val << std::endl;
}


int main() {
    std::thread p(producer);
    std::thread c(consumer);
    p.join();
    c.join();
}
