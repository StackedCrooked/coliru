#include <vector>
#include <ctime>
#include <iostream>
 
struct Noisy {
    Noisy() {std::cout << "constructed\n"; }
    Noisy(const Noisy&) { std::cout << "copied\n"; }
    Noisy(Noisy&&) { std::cout << "moved\n"; }
    ~Noisy() {std::cout << "destructed\n"; }
    
    std::time_t tm;
};
 

Noisy fn_move()
{
    Noisy n1, n2;
    n1.tm = std::time(0);
    n2.tm = std::time(0);    
    
    if( std::time(0) % 2 )
        return std::move(n1);
    else
    	return std::move(n2);
}

Noisy fn_nrvo()
{
    Noisy n1, n2;
    n1.tm = std::time(0);
    n2.tm = std::time(0);    
    
    if( std::time(0) % 2 )
    	return n1;
    else
    	return n2;
}
 
int main()
{
	{
    	Noisy n = fn_move();
    	std::cout << n.tm << '\n';
	}
	
	std::cout << "---------------------\n";
	
	{
    	Noisy n = fn_nrvo();
    	std::cout << n.tm << '\n';
	}
}