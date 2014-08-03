    #include <iostream>
    #include <thread>
    #include <chrono>
    
    using namespace std;
    
    void foo() {
        cout << "Hello from foo()!" << endl;
    }
    
    struct timed_execution {
        typedef void (*func_type)(void);
        timed_execution(func_type func, const std::chrono::duration period) 
            : func_(func)
            , period_(period)
            , thread_(std::bind(this,timed_execution<func_type>::threadFunc))
        {
        }
    private:        
        void threadFunc() {
            while(true) {
                std::this_thread::sleep_for(period_);
                func_();
            }
        }
        func_type func_;
        const std::chrono::duration period_;
        std::thread thread_;
    };
    
    int main() {
    	timed_execution t(foo,std::chrono::milliseconds(2000));

        std::this_thread::sleep_for(std::chrono::seconds(60));
        return 0;
    }
