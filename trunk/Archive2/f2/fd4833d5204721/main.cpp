#include <iostream>
#include <chrono>

int main()
{
    using namespace std::chrono;    
    minutes m{60};
    seconds s{3600};
    hours h{1};
    std::cout << (duration_cast<seconds>(m).count() == s.count());
    std::cout << (duration_cast<seconds>(h).count() == s.count());
    std::cout << (duration_cast<minutes>(s).count() == m.count());
    std::cout << (duration_cast<minutes>(h).count() == m.count());
    std::cout << (duration_cast<hours>(s).count() == h.count());
    std::cout << (duration_cast<hours>(m).count() == h.count());
    
    // Bonus
    std::cout << (s == m) << (m == h);
}
