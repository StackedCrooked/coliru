#include <iostream>
#include <stdexcept>
#include <ctime>
#include <iomanip>

#define ERROR -1
#define NO_ERR 0

int returner(int& result, std::string in, int count, int freq) noexcept {
    if (count<1) { //base case
        if (freq==0) //ERROR
            return ERROR;
        else {
            result += 1;//return result
            return NO_ERR;
        }
    }
    
    if (returner(result, in, count-1, freq) == -1) return -1; //maybe error
    if (returner(result, in, count-1, freq) == -1) return -1; //maybe error
    result += in.capacity(); //return result
    return NO_ERR;
}

int thrower_recursive(std::string in, int count, int freq) {
    if (count<1) { //base case
        if (freq==0) //ERROR
            throw std::logic_error("OMG BAD");
        else
            return 1; //return result
    }
    
    int r = thrower_recursive(in, count-1, freq); //maybe error
    r += thrower_recursive(in, count-1, freq); //maybe error
    return r + in.capacity(); //return result
}
//match the return value API
int thrower(int& result, const std::string& in, int count, int freq) {
    result = thrower_recursive(in, count, freq);
    return 0;
}

template<class func_type>
void do_test(func_type func, const char* name) {
    const int tests = 12345;
    const int depth = 10;
    const int error_frequency = 1000;
    
    clock_t begin = clock();
    int result=0;
    int was_error = 0;
    for (int i = 0; i < tests; ++i) {
        try {
            was_error = func(result, "STRING", depth, i%error_frequency);
        } catch (const std::exception& v) {
            was_error = ERROR;
        }
    }
    clock_t end = clock();
    
    double rate = (100.0/error_frequency);
    unsigned ns = 1000000*(end-begin)/CLOCKS_PER_SEC/tests;
    std::cout << name << ": ";
    std::cout << tests << " loops " << depth << " deep with ";
    std::cout << rate << "% error rate ";
    std::cout << "in " << std::setw(7) << (end-begin) << " ticks: ";
    std::cout << ns << "ns average. ";
    std::cout << "nocheat value: " << result << was_error << '\n';
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    do_test(thrower, "throw ");
    do_test(thrower, "throw ");
    do_test(returner, "return");
    do_test(returner, "return");
    do_test(thrower, "throw ");
    do_test(thrower, "throw ");
}