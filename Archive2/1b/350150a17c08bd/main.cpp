#include <iostream>
#include <atomic>
#include <thread>

void philosopher(
                const int philosopher_index,
                volatile std::atomic_int& left_frok,
                volatile std::atomic_int& right_fork,
                int& eaten_portions_counter,
                volatile std::atomic_int& totall_portions_left
                )
{
    
    for(;;)
    {
        int nobodys_fork = 0;        
        
        if(!left_frok.compare_exchange_weak(
                                            nobodys_fork,
                                            philosopher_index,
                                            std::memory_order_acquire,
                                            std::memory_order_relaxed
                                           )
                                            )
        {
            continue;
        }
    
        if(!right_fork.compare_exchange_weak(
                                            nobodys_fork,
                                            philosopher_index,
                                            std::memory_order_acquire,
                                            std::memory_order_release
                                           ))
        {
            left_frok = 0;
            
            continue;
        }
        
        if(totall_portions_left-- < 0)
        {
            return;
        }
        eaten_portions_counter++;
        
        right_fork = 0;
        left_frok  = 0;
    }
}

int main()
{
    std::atomic_int forks[] = {{0}, {0}, {0}, {0}, {0}};
    std::atomic_int totall_portions = {1000};
    int portions_eaten_by_philosopher[] = {0, 0, 0, 0, 0};
    std::thread philosofers[] = {
                       {philosopher, 1, forks[0], forks[1], portions_eaten_by_philosopher[0], totall_portions},
                       {philosopher, 2, forks[1], forks[2], portions_eaten_by_philosopher[1], totall_portions},
                       {philosopher, 3, forks[2], forks[3], portions_eaten_by_philosopher[2], totall_portions},
                       {philosopher, 4, forks[3], forks[4], portions_eaten_by_philosopher[3], totall_portions},
                       {philosopher, 5, forks[4], forks[0], portions_eaten_by_philosopher[4], totall_portions}
                                };
    
    philosofers[0].join();
    philosofers[1].join();
    philosofers[2].join();
    philosofers[3].join();
    philosofers[4].join();
    
    std::cout << "Tatall portions left value ant the end = " << totall_portions << std::endl;
    std::cout << "1 st philosofer has eaten " << portions_eaten_by_philosopher[0] << " portions " << std::endl;
    std::cout << "2 nd philosofer has eaten " << portions_eaten_by_philosopher[1] << " portions " << std::endl;
    std::cout << "3 rd philosofer has eaten " << portions_eaten_by_philosopher[2] << " portions " << std::endl;
    std::cout << "4 th philosofer has eaten " << portions_eaten_by_philosopher[3] << " portions " << std::endl;
    std::cout << "5 th philosofer has eaten " << portions_eaten_by_philosopher[4] << " portions " << std::endl;
}

