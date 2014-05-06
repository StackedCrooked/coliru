#include <iostream>
#include <algorithm>
#include <array>

struct Pair {
    std::array<int,2> data;
    int first() const { return data[0]; }
    int second() const { return data[1]; }
    friend inline bool operator< ( const Pair & p1, const Pair & p2 ) {
        return p1.first() < p2.first();
    }
};

int main() {
	int N=5;
	int data[10]= {1,2,7,8,13,14,10,11,4,5};
	Pair* pairs( reinterpret_cast<Pair*>(data) );
	
	std::cout << "unsorted" << std::endl;
	for(int i=0; i<N; ++i)
		std::cout << i << ": (" << pairs[i].first() << ", " << pairs[i].second() << ")" << std::endl;
	
	std::sort(pairs, pairs+N);
	
	std::cout << "sorted" << std::endl;
	for(int i=0; i<N; ++i)
		std::cout << i << ": (" << pairs[i].first() << ", " << pairs[i].second() << ")" << std::endl;
	return 0;
}