#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int main() {
    int solution = 0;
    
    int input[] = {1,2,3,4,5,6,7,8,9};
    std::set<int> products;

    do {
		std::string permutation;
		for (const auto& e : input) {
			permutation += std::to_string(e);
		}

		for (int i = 0; i < 4; i++) {
			const int multiplicand = std::stoi(permutation.substr(0,i + 1));
			
			for (int j = 0; j < 4; j++) {
				const int multiplier = std::stoi(permutation.substr(i + 1, j + 1));
				const int product = std::stoi(permutation.substr(j + i + 2, permutation.size()));
				
				if (multiplicand * multiplier == product) {
					products.insert(product);
				}
			}
		}
    } 
    while ( std::next_permutation(input,input + 9) );
    
	for (const auto& e : products) {
		solution += e;
	}

    std::cout << "Solution: " << solution << std::endl;
}
    