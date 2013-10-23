#include <chrono>
#include <ratio>
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>

struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};

struct Foo2 {
    void display_greeting() {
        std::cout << "Hello, world.\n";
    }
    void display_number(int i) {
        std::cout << "number: " << i << '\n';
    }
    int data = 7;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};


int main()
{
    // chrono
    {
        std::chrono::hours h(1); // one hour
        std::chrono::milliseconds ms{3}; // 3 milliseconds
        std::chrono::duration<int, std::kilo> ks(3); // 3000 seconds
     
        // error: treat_as_floating_point<int>::value == false,
        // This duration allows whole tick counts only
    //  std::chrono::duration<int, std::kilo> d3(3.5);
     
        // 30Hz clock using fractional ticks
        std::chrono::duration<double, std::ratio<1, 30>> hz30(3.5);
     
        // 3000 microseconds constructed from 3 milliseconds
        std::chrono::microseconds us = ms;
        // error: 1/1000000 is not divisible by 1/1000
    //  std::chrono::milliseconds ms2 = us

    }
    
    // rational
    {
        typedef std::ratio<2, 3> two_third;
        typedef std::ratio<1, 6> one_sixth;
     
        typedef std::ratio_add<two_third, one_sixth> sum;
        std::cout << "2/3 + 1/6 = " << sum::num << '/' << sum::den << '\n';
        
      
 
        typedef std::ratio_subtract<two_third, one_sixth> diff;
        std::cout << "2/3 - 1/6 = " << diff::num << '/' << diff::den << '\n';
        
        typedef std::ratio_multiply<two_third, one_sixth> r;
        std::cout << "2/3 * 1/6 = " << r::num << '/' << r::den << '\n';
    
        typedef std::ratio_divide<two_third, one_sixth> r2;
        std::cout << "2/3 / 1/6 = " << r2::num << '/' << r2::den << '\n';
    }
    
    // more algorithms
    {
        // fill
        {
            int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            std::vector<int> v1(data, data+10);
         
            std::fill(v1.begin(), v1.end(), -1);
         
            for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
        
        // generate
        {
            std::vector<int> v(5);
            std::generate(v.begin(), v.end(), std::rand); // Using the C function rand()
         
            std::cout << "v: ";
            for (auto iv: v) {
                std::cout << iv << " ";
            }
            std::cout << "\n";
         
            // Initialize with default values 0,1,2,3,4 from a lambda function
            int n(0);
            std::generate(v.begin(), v.end(), [&]{ return n++; }); 
         
            std::cout << "v: ";
            for (auto iv: v) {
                std::cout << iv << " ";
            }
            std::cout << "\n";
        }
        
        // rotate
        {
            std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1}; 
 
            std::cout << "before sort:      ";
            for (int n: v)
                std::cout << n << ' ';
            std::cout << '\n';
         
            // insertion sort
            for (auto i = v.begin(); i != v.end(); ++i) {
                std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
            }
         
            std::cout << "after sort:       ";
            for (int n: v)
                std::cout << n << ' ';
            std::cout << '\n';
         
            // simple rotation to the left
            std::rotate(v.begin(), v.begin() + 1, v.end());
         
            std::cout << "simple rotate left  : ";
            for (int n: v)
                std::cout << n << ' ';
            std::cout << '\n';
         
            // simple rotation to the right
            std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
         
            std::cout << "simple rotate right : ";
            for (int n: v)
                std::cout << n << ' ';
            std::cout << '\n';
        }
        
        // reverse
        {
            std::vector<int> v({1,2,3});
            std::reverse(std::begin(v), std::end(v));
            std::cout << v[0] << v[1] << v[2] << '\n';
         
            int a[] = {4, 5, 6, 7};
            std::reverse(&a[0], &a[4]);
            std::cout << a[0] << a[1] << a[2] << a[3] << '\n';
        }
        
        // unique
        {
            
            std::vector<int> v{1, 2, 2, 2, 3, 3, 2, 2, 1};
            std::vector<int>::iterator last;
         
            last = std::unique(v.begin(), v.end()); // 1 2 3 2 1 3 2 2 1
                                                    //           ^
            for (std::vector<int>::iterator it = v.begin(); it != last; ++it) {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
        
        // is_permutation
        {
            std::vector<int> v1{1,2,3,4,5};
            std::vector<int> v2{3,5,4,1,2};
            std::cout << "3,5,4,1,2 is a permutation of 1,2,3,4,5? "
                      << std::boolalpha
                      << std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n';
         
            std::vector<int> v3{3,5,4,1,1};
            std::cout << "3,5,4,1,1 is a permutation of 1,2,3,4,5? "
                      << std::boolalpha
                      << std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';
        }
    }
    
    //std::function
    {
        // store a free function
        std::function<void(int)> f_display = print_num;
        f_display(-9);
     
        // store a lambda
        std::function<void()> f_display_42 = []() { print_num(42); };
        f_display_42();
     
        // store the result of a call to std::bind
        std::function<void()> f_display_31337 = std::bind(print_num, 31337);
        f_display_31337();
     
        // store a call to a member function
        std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
        Foo foo(314159);
        f_add_display(foo, 1);
     
        // store a call to a function object
        std::function<void(int)> f_display_obj = PrintNum();
        f_display_obj(18);
    }
    
    //mfun
    {
        Foo2 f;
 
        auto greet = std::mem_fn(&Foo2::display_greeting);
        greet(f);
     
        auto print_num = std::mem_fn(&Foo2::display_number);
        print_num(f, 42);
     
        auto access_data = std::mem_fn(&Foo2::data);
        std::cout << "data: " << access_data(f) << '\n';
    }
}