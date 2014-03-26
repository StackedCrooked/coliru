unsigned long long phi(unsigned long x) {
    unsigned long long ret = 1;
    unsigned long long pow;
    
    for (unsigned long long i = 2; x != 1; i++) {
        pow = 1;
        while (!(x % i)) {
            x /= i;
            pow *= i;
        }
        ret *= (pow - (pow/i));
    }
    return ret;
}

int main() {
    LargeInt solution = 0;
    for (int n = 1; n <= 90000; n++) {
        solution += phi(n);
    }
    std::cout << "Solution: " << solution << std::endl;
}