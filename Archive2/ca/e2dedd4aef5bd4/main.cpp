    #include <iostream>
    #include <thread>
    #include <chrono>
    #include <functional>
    
    using namespace std;
    
    void foo() {
        cout << "Hello from foo()!" << endl;
    }
    
    template<typename CALLBACK_T>
    struct timer {
        
        template<typename D>
        timer(CALLBACK_T func, const D& period) 
            : func_(func)
            , period_(std::chrono::duration_cast<std::chrono::milliseconds>( period ))
            , thread_(std::bind(&timer::threadFunc,this))
        {
        }
    private:        
        void threadFunc() {
            while(true) {
                std::this_thread::sleep_for(period_);
                func_();
            }
        }
        CALLBACK_T func_;
        const std::chrono::milliseconds period_;
        std::thread thread_;
    };
    
    template<typename CALLBACK_T , typename D>
    timer<typename std::decay<CALLBACK_T>::type> make_timer( CALLBACK_T&& callback , D&& duration )
    {
        return { std::forward<CALLBACK_T>( callback ) , std::forward<D>( duration ) };   
    }
    
    int main() {
    	auto timer = make_timer(foo,std::chrono::seconds(1));
        auto other = make_timer( [](){ std::cout << "Hello from lambda!\n"; } , std::chrono::seconds{ 1 } );

        std::this_thread::sleep_for(std::chrono::seconds(60));
        return 0;
    }
