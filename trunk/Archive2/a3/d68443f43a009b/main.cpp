#include <iostream>
#include <vector>
#include <string>

bool Prime(int number){
    if (number % 2 == 0) {
        return false;
    }
    for (int i = 3; (i * i) <= number; i += 2){
        if (number % i == 0 ) {

            return false;
        }
    }
    return true;
}

int main() {
    const int rangeGuess = 40000;
    int solution = rangeGuess * 10;

    std::vector<int> primes;

    for (int i = 3; i < rangeGuess; i += 2) {
        if (!Prime(i)) {
            continue;
        }
        for (int j = i + 2; j < rangeGuess; j += 2) {
            if (!Prime(j)) {
                continue;
            }
            for (int k = j + 2; k < rangeGuess; k += 2) {
                if (!Prime(k)) {
                    continue;
                }
                for (int l = k + 2; l < rangeGuess; l += 2) {
                    if (!Prime(l)) {
                        continue;
                    }
                    for (int m = l + 2; m < rangeGuess; m += 2) {
                        if (!Prime(m)) {
                            continue;
                        }
                        primes.push_back(i);
                        primes.push_back(j);
                        primes.push_back(k);
                        primes.push_back(l);
                        primes.push_back(m);

                        bool shouldHold = false;
                        for (const auto e : primes) {
                            for (const auto j : primes) {
                                if (e == j) {
                                    continue;
                                }

                                if (Prime(std::stoi(std::string(std::to_string(e) + std::to_string(j))))
                                    && Prime(std::stoi(std::string(std::to_string(j) + std::to_string(e))))) {
                                    shouldHold = true;
                                }
                            }
                        }

                        int sum = i + j + k + l + m;
                        if (shouldHold && sum < solution) {
                            solution = sum;
                        }
                        primes.clear();
                    }
                }
            }
        }
    }

    std::cout << "Solution: " << solution << std::endl;
}
