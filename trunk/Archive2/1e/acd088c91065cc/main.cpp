#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
 
int main()
{
    std::time_t t = std::time(nullptr);
    std::tm ct = *std::gmtime(&t);
    ct.tm_min = ct.tm_sec = 0;
    ct.tm_hour = 18;
    ct.tm_mday++;
    t = std::mktime(&ct);
    
    std::chrono::system_clock::time_point tomorrow_at_6 = std::chrono::system_clock::from_time_t(t);

    std::cout << "There's only " << std::chrono::duration<double, std::ratio<3600>>(tomorrow_at_6 - std::chrono::system_clock::now()).count() << " hours left until tomorrow 6 pm\n";
}