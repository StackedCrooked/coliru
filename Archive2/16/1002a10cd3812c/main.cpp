#include <chrono>
#include <iostream>
int main()
{
    // simple arithmetic
    std::chrono::seconds s = std::chrono::hours(9) 
                             + 2*std::chrono::minutes(10)
                             + std::chrono::seconds(70)/10;
 
    std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
 
    // difference between dividing a duration by a number
    // and dividing duration by another duration
    std::cout << "Dividing that by 2 minutes gives "
              << s / std::chrono::minutes(2) << '\n';
    std::cout << "Dividing that by 2 gives "
              << (s / 2).count() << " seconds\n";
 
   // the remainder operator is useful in determining where in a time
   // frame is this particular duration, e.g. to break it down into hours,
   // minutes, and seconds:
   std::cout << s.count() << " seconds is "
             << std::chrono::duration_cast<std::chrono::hours>(
                    s
                ).count() << " hours, "
             << std::chrono::duration_cast<std::chrono::minutes>(
                    s % std::chrono::hours(1)
                ).count() << " minutes, "
             << std::chrono::duration_cast<std::chrono::seconds>(
                    s % std::chrono::minutes(1)
                ).count() << " seconds\n";
}