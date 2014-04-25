#include <iostream>
#include <chrono>
#include <vector>
#include <stdexcept>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

using std::cout;
using std::endl;

int main() {

    class B {
  	public: int i;
  		B() {
     		i = 123;
  		}
  		~B() {}
  		int get() const { return i; }
	};

    B * b = new B();

    //first solution
	class A:public B {
	public: int j;
		A() {}
		~A() {}
		int somethingMethod(int n) {
  			j = get() * n;
  			return j;
		}
	};

	//second solution
	class C {
	public: int j;
		B * b;
		C(B * _b):b(_b) {}
		~C() {}
		int somethingMethod(int n) {
  			j = b->get() * n;
  			return j;
		}
	};

    for( size_t m=10; m <= 1000; m*=10 ) {
        std::vector<A> a(m);
        std::vector<C> c(m,C(b));

        for( size_t n=10; n <= 1000; n*=10 ) {
            std::vector<int> x(n);
            for( auto & it : x ) it = rand();
    
            auto start = steady_clock::now();
            uint64_t first_sum = 0;
            for(auto & t : a) for( auto it : x ) first_sum += t.somethingMethod(it);
            auto first_nsec = duration_cast<nanoseconds>(steady_clock::now() - start).count(); 
    
            start = steady_clock::now();
            uint64_t second_sum = 0;
            for(auto & t : c) for( auto it : x ) second_sum += t.somethingMethod(it);
            auto second_nsec = duration_cast<nanoseconds>(steady_clock::now() - start).count(); 
        
            if (first_sum != second_sum) throw std::runtime_error("sums differ");
            double ratio = double(first_nsec) / double(second_nsec);

            cout << "m=" << m << " n=" << n << "," << ratio << endl;
        }
    }
    
    delete b;

	return 0;
}