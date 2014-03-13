#include <iostream>
#include <future>

//=======================================================================================!
struct DoWork
{
    DoWork(int cycles, int restTime) : _cycles(cycles), _restTime(restTime), _stop(false)
    {
    }

    int operator () ()
    {
        for(int i = 0 ; i < _cycles; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(_restTime));
            if(_stop) return 42;

            doTask();
        }
        return 13;
    }

    void stop()
    {
        _stop = true;
    }

private:
    void doTask()
    {
        std::cout << "doing task!" << std::endl;
    }

private:
    int _cycles;
    int _restTime;
    std::atomic<bool> _stop;
};

//=======================================================================================!

int main()
{
    DoWork doObj(50, 500);
    std::future<int> f = std::async(std::launch::async, std::ref(doObj));

    std::cout << "Should I stop work ?" << std::endl;
    std::cout << "('1' = Yes, '2' = no, 'any other' = maybe)" << std::endl;
    int answer;
    std::cin >> answer;

    if(answer == 1) doObj.stop();

    std::cout << f.get() << std::endl;
}
//=======================================================================================!
