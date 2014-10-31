#include <chrono>
#include <iostream>
#include <stdexcept>
#include <climits>
#include <array>
#include <algorithm>
#include <iostream>
#include <cstdio>

static const unsigned error_frequency = 100000; //every 1000 operations will have an error
static const unsigned loop_count = 1000; //do the loop for a thousasnd error/exceptions

//__declspec(noinline) unsigned function_with_error_code(unsigned* i) {
unsigned __attribute__ ((noinline)) function_with_error_code(unsigned* i) noexcept {
    static unsigned counter=0;    
    if (++counter == error_frequency) {
        counter = 0;
        return 1;
    }
    *i *= 10;        
    return 0;
}
//__declspec(noinline) unsigned function_with_exception(unsigned* i) {
void __attribute__ ((noinline)) function_with_exception(unsigned* i) {
    static unsigned counter=0; 
    if (++counter == error_frequency) {
        counter = 0;
        throw std::runtime_error("");
    }
    *i *= 10; 
}

unsigned loop_with_error_codes() noexcept {
    unsigned value = 1;
    unsigned error_code = 0;
    for(unsigned i=0; i<=INT_MAX && error_code==0; ++i) 
        error_code = function_with_error_code(&value);
    if (error_code == 0)
        printf("%d, value);
    return error_code;
}
void loop_with_exceptions() {
    unsigned value = 1;
    for(unsigned i=0; i<=INT_MAX; ++i)
        function_with_exception(&value);
    printf("%d, value);
}

void time_error_codes() {
    std::array<unsigned, loop_count> results = {{}};
    std::chrono::high_resolution_clock::time_point start(std::chrono::high_resolution_clock::now());
    for(unsigned i=0; i<loop_count; ++i) {
        unsigned error = loop_with_error_codes();
        if (!error)
            results[i] = 0;
        else
            results[i] = 1;            
    }
    std::chrono::high_resolution_clock::time_point stop(std::chrono::high_resolution_clock::now());
    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    unsigned result = std::count(results.begin(), results.end(), 1);
    std::cout << "error codes\tfound " << result << "\tin " << duration.count() << "ns\n";
}
void time_exceptions() {
    std::array<unsigned, loop_count> results = {{}};
    std::chrono::high_resolution_clock::time_point start(std::chrono::high_resolution_clock::now());
    for(unsigned i=0; i<loop_count; ++i) {
            try {
                loop_with_exceptions();
                results[i] = 0;
            } catch(const std::exception& e) {
                results[i] = 1;
            }
        }
    std::chrono::high_resolution_clock::time_point stop(std::chrono::high_resolution_clock::now());
    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    unsigned result = std::count(results.begin(), results.end(), 1);
    std::cout << "exceptions\tfound " << result << "\tin " << duration.count() << "ns\n";
}

int main() {
    time_error_codes();
    time_exceptions();
    time_exceptions();
    time_error_codes();
    time_error_codes();
    time_exceptions();
    return 0;
}

/*
MSVC RESULTS:
error codes     found 1000  in 279555900ns
exceptions      found 1000  in 366573300ns
exceptions      found 1000  in 319563900ns
error codes     found 1000  in 302560500ns
error codes     found 1000  in 445089000ns
exceptions      found 1000  in 354070800ns

G++ RESULTS:
error codes     found 1000	in 498687044ns
exceptions	    found 1000	in 622493149ns
exceptions	    found 1000	in 624723186ns
error codes	    found 1000	in 399746055ns
error codes	    found 1000	in 445914296ns
exceptions	    found 1000	in 641108930ns

CLANG++ RESULTS:
error codes     found 1000	in 535996522ns
exceptions	    found 1000	in 481802256ns
exceptions	    found 1000	in 455776903ns
error codes	    found 1000	in 476380551ns
error codes	    found 1000	in 498068455ns
exceptions	    found 1000	in 517649965ns
*/
