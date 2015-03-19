
#include <cstdio>
#include <vector>

int main(){

    std::vector<unsigned> tomatoes = { 2, 3 };
	std::vector<unsigned> potatoes = { 10, 3, 1 };

    potatoes.reserve(potatoes.size() + tomatoes.size() + 1);
    
	for (unsigned i : tomatoes){
		for (auto iter = potatoes.rbegin(); iter != potatoes.rend(); ++iter){
			if (i < *iter){
				//printf("%u\n", *iter);
				potatoes.insert(iter.base(), i); // problem line, causes the segfault
			}
		}
	}

	for (unsigned i : potatoes){
		printf("%u, ", i);
	}

	printf("\n");

	return 0;
}
