#include <iostream>
#include <cstdint>
#include <map>


class RabbitSolver {
    
public:
    RabbitSolver(int n, int m);
    
    std::uint64_t F(const int n, bool exception = false) 
    {
        if (memo.count(n) && !exception) {
            return memo[n];
        }
        else {
            auto val = _F(n, exception);
            memo[n] = val;
            return val;
        }
    }
    
    std::uint64_t _F(const int n, bool exception) 
    {
    	if (n == 0 && exception) {
    		return 1;
    	}
    	else if (n < 0) {
    		return 0;
    	}
    	else if (n == 1) {
    		return 1;
    	}
    	else if (n == 2) {
    		return 1;
    	}
    	
    	return F( n - 1 ) + F ( n - 2 ) - F (n - (m + 1), true);
    }
    
    uint64_t Solve() {
        return F(n);    
    }
    
private:
    std::map<int, std::uint64_t> memo;
    const int n;
    const int m;
    
};

RabbitSolver::RabbitSolver(int n, int m) 
    : n( n ),
    m( m )
{
}

int main() {
    RabbitSolver r(89, 19);
    std::cout << r.Solve();
}





