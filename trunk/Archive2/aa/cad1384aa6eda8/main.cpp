#include <iostream>
#include <thread>
#include <memory>

class base {
    public:
        base() {
            std::cout << "base()" << std::endl;
        }
        virtual ~base() {
            std::cout << "~base()" << std::endl;
        }
        base(const base&) = delete;
        base(base&&) = delete;
        base& operator=(const base&) = delete;
        base& operator=(base&&) = delete;
};

class derived final : public base {
    public:
        derived() {
            std::cout << "derived()" << std::endl;
        }
        virtual ~derived() {
            std::cout << "~derived()" << std::endl;
        }
};


void foo() {
    static thread_local std::unique_ptr<base> ptr;
    if (!ptr) {
        std::cout << "new ptr:" << std::this_thread::get_id() << std::endl;
        ptr.reset(new derived());
    } else {
        std::cout << "release ptr:" << std::this_thread::get_id() << std::endl;
        ptr.release();
    }
}

void thread_main() {
    foo();
    foo();
}

int main()
{
    std::thread thread1(thread_main);
    thread1.join();
    return 0;
}