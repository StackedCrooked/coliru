/**
 *   Copyright 2011 Travis Gockel
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
**/

// Turn building and testing boost::bind on or off with this macro
//#define USE_BOOST 1

// workaround for varieties of g++-4.6 with --std=gnu++0x
#ifndef _GLIBCXX_USE_NANOSLEEP
#   define _GLIBCXX_USE_NANOSLEEP
#endif

#include <cstdint>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#if USE_BOOST
#include <boost/function.hpp>
#include <boost/bind.hpp>
#endif

class timer
{
public:
    typedef std::chrono::high_resolution_clock clock;
    typedef clock::time_point                  time_point;
    typedef clock::duration                    duration;
    
public:
    timer()
    {
        reset();
    }
    
    void reset()
    {
        _starttime = clock::now();
    }

    duration elapsed() const
    {
        return clock::now() - _starttime;
    }
protected:
    time_point _starttime;
};

bool test_timer()
{
    using std::chrono::milliseconds;
    typedef timer::duration duration;
    
    const milliseconds sleep_time(500);
    
    timer t;
    std::this_thread::sleep_for(sleep_time);
    duration recorded = t.elapsed();
    
    // make sure the clock and this_thread::sleep_for is precise within one millisecond (or at least in agreement as to
    // how inaccurate they are)
    return (recorded - milliseconds(1) < sleep_time)
        && (recorded + milliseconds(1) > sleep_time);
}

template <typename T>
void volatile_write(const T& x)
{
    volatile T* p = new T;
    *p = x;
    delete p;
}

template <typename Function>
void run_test(const std::string& name, Function func)
{
    std::cout << name;
    timer t;
    volatile_write(func());
    timer::duration duration = t.elapsed();
    std::cout << '\t' << duration.count() << std::endl;
}

template <typename Function>
void do_test_loop(Function func, const uint64_t upper_limit = 1000000000ULL)
{
    for (uint64_t i = 0; i < upper_limit; ++i)
        func(i);
}

uint64_t test_accumulate_lambda()
{
    uint64_t x = 0;
    auto accumulator = [&x] (uint64_t i) { x += i; };
    do_test_loop(accumulator);
    return x;
}

void test_accumulate_bind_function(uint64_t& x, uint64_t i)
{
    x += i;
}

uint64_t test_accumulate_bind()
{
    namespace arg = std::placeholders;
    
    uint64_t x = 0;
    std::function<void (uint64_t)> accumulator = std::bind(&test_accumulate_bind_function, std::ref(x), arg::_1);
    do_test_loop(accumulator);
    return x;
}

uint64_t test_accumulate_bound_lambda()
{
    uint64_t x = 0;
    std::function<void (uint64_t)> accumulator = [&x] (uint64_t i) { x += i; };
    do_test_loop(accumulator);
    return x;
}

#if USE_BOOST
uint64_t test_accumulate_boost_bind()
{
    uint64_t x = 0;
    
    boost::function<void (uint64_t)> accumulator = boost::bind(&test_accumulate_bind_function, boost::ref(x), _1);
    do_test_loop(accumulator);
    return x;
}

uint64_t test_accumulate_boost_bound_lambda()
{
    uint64_t x = 0;
    boost::function<void (uint64_t)> accumulator = [&x] (uint64_t i) { x += i; };
    do_test_loop(accumulator);
    return x;
}
#endif

int main()
{
    if (!test_timer())
    {
        std::cout << "Failed timer test." << std::endl;
        return -1;
    }
    
    run_test("Accumulate (lambda)            ", &test_accumulate_lambda);
    run_test("Accumulate (bind)              ", &test_accumulate_bind);
    run_test("Accumulate (bound lambda)      ", &test_accumulate_bound_lambda);
    #if USE_BOOST
    run_test("Accumulate (boost bind)        ", &test_accumulate_boost_bind);
    run_test("Accumulate (boost bound lambda)", &test_accumulate_bound_lambda);
    #endif
}
