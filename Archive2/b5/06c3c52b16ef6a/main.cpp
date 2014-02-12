#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <cmath>

int main() {
    unsigned long long solution = 0;
    std::map<int, unsigned long long> cubes;
    
    for (int i = 4500;;i++) {
        std::cout << i << std::endl;
        //Insert cube
        const unsigned long long cube = i * i * i;
        cubes.insert(std::make_pair(i,cube));
        
        //Create permutation format
        std::vector<int> cubePerm;
        for (const auto e : std::to_string(cube)) {
            cubePerm.push_back(e - '0');    
        }
        std::sort(cubePerm.begin(),cubePerm.end());
        
        //Check permutations for cubes
        std::vector<unsigned long long> permutations;
        
        do {
            std::string currentPerm = "";
            for (const auto e : cubePerm) {
                currentPerm += std::to_string(e);
            }
            
            const unsigned long long currentULL = std::stoull(currentPerm);
            
            for (const auto& f : cubes) {
                if (f.second == currentULL && std::to_string(f.second).size() == std::to_string(currentULL).size()) {
                    permutations.push_back(currentULL);
                }
            }
        } 
        while (std::next_permutation(cubePerm.begin(),cubePerm.end()));
        
        //If permutations
        if (permutations.size() == 5) {
            std::sort(permutations.begin(), permutations.end());
            solution = permutations[0];
            break;
        }
    }
    
    std::cout << "Solution: " << solution << std::endl;
}