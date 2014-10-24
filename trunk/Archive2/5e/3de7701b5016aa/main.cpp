#include <iostream>
#include <functional>
#include <thread>
#include <atomic>

class Runnable
{
public:
    Runnable() : m_stop(), m_thread() { }
    virtual ~Runnable() { try { stop(); } catch(...) { /*??*/ } }

    Runnable(Runnable const&) = delete;
    Runnable& operator =(Runnable const&) = delete;

    void stop() { m_stop = true; m_thread.join(); }
    void start() { m_thread = std::thread(&Runnable::run, this); }

protected:
    virtual void run() = 0;
    std::atomic<bool> m_stop;

private:
    std::thread m_thread;
};


class TruckProducer : public Runnable
{
std::function<void()> truckReceiver;
public:
    TruckProducer(std::function<void()> _truckReceiver) : truckReceiver(_truckReceiver) 
    {
        
    };
    void run()
    {
        std::mt19937::result_type seed = (size_t)time(0) + std::this_thread::get_id().hash() ;
		//some random time as task ask us:
		auto dice_rand = std::bind(std::uniform_int_distribution<int>(Const::X_MACHINE_ARRIVE_TIME_MIN,Const::X_MACHINE_ARRIVE_TIME_MAX),std::mt19937(seed));
		std::chrono::milliseconds rnd_time( dice_rand() );
		std::this_thread::sleep_for( rnd_time );
        truckReceiver();
    }
};    

void p() {
        
};

int main(int nArgs, char *args[]) {
    std::cout<<"Hello!";
    TruckProducer pro(p);
    return 0;
}