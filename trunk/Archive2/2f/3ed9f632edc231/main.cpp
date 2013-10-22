#include <numeric>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>

#include <algorithm>


 
int main()
{
    // partial sum
    {
        std::vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
     
        std::cout << "The first 10 even numbers are: ";
        std::partial_sum(v.begin(), v.end(), 
                         std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
     
        std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>());
        std::cout << "The first 10 powers of 2 are: ";
        for (auto n : v) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }
    
    // all, any, none
    {
        std::vector<int> v(10, 2);
        std::partial_sum(v.cbegin(), v.cend(), v.begin());
        std::cout << "Among the numbers: ";
        std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
     
        if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
            std::cout << "All numbers are even\n";
        }
        if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                         std::placeholders::_1, 2))) {
            std::cout << "None of them are odd\n";
        }
        struct DivisibleBy
        {
            const int d;
            DivisibleBy(int n) : d(n) {}
            bool operator()(int n) const { return n % d == 0; }
        };
     
        if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
            std::cout << "At least one number is divisible by 7\n";
        }
    }
    
    // find
    {
        int n1 = 3;
        int n2 = 5;
     
        std::vector<int> v{0, 1, 2, 3, 4};
     
        auto result1 = std::find(v.begin(), v.end(), n1);
        auto result2 = std::find(v.begin(), v.end(), n2);
        auto result3 = std::find_if(v.begin(), v.end(), [](int x){return x == 2;});
        auto result4 = std::find_if_not(v.begin(), v.end(), [](int x){return x == 2;});
     
        if (result1 != v.end()) {
            std::cout << "v contains: " << n1 << '\n';
        } else {
            std::cout << "v does not contain: " << n1 << '\n';
        }
     
        if (result2 != v.end()) {
            std::cout << "v contains: " << n2 << '\n';
        } else {
            std::cout << "v does not contain: " << n2 << '\n';
        }
        
        if (result3 != v.end()) {
            std::cout << "v contains: " << 2 << '\n';
        } else {
            std::cout << "v does not contain: " << 2 << '\n';
        }
    }
    
    //count
    {
        int data[] = { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
        std::vector<int> v(data, data+10);
 
        int num_items1 = std::count_if(v.begin(), v.end(), [](int i) {return i % 3 == 0;});
 
        std::cout << "number divisible by three: " << num_items1 << '\n';
    }
    
    //copy
    {
        std::vector<int> from_vector;
        for (int i = 0; i < 10; i++) {
            from_vector.push_back(i);
        }
     
        std::vector<int> to_vector(10);
     
        /*std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
     
        std::cout << "to_vector contains: ";
        std::copy(to_vector.begin(), to_vector.end(), 
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        to_vector.clear();
        */
        std::copy_if(from_vector.begin(), from_vector.end(), to_vector.begin(),
            [](int x){return x % 2 == 0;});
        
        std::cout << "to_vector contains: ";
        std::copy(to_vector.begin(), to_vector.end(), 
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
    }
    
    //remove
    {
        std::string str1 = "Text with some   spaces";
        str1.erase(std::remove(str1.begin(), str1.end(), ' '),
                   str1.end());
        std::cout << str1 << '\n';
     
        std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
        str2.erase(std::remove_if(str2.begin(), 
                                  str2.end(),
                                  [](char x){return std::isspace(x);}),
                   str2.end());
        std::cout << str2 << '\n';
    }
    
    // accumulate
    {
        
        auto  multiply = [](int x, int y) -> int
        {
            return x*y;
        };
 
        auto magic_function = [](std::string res, int x) -> std::string
        {
            return res += (x > 5) ? "b" : "s";
        };
        
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
 
        int sum = std::accumulate(v.begin(), v.end(), 0);
        int product = std::accumulate(v.begin(), v.end(), 1, multiply);
        std::string magic = std::accumulate(v.begin(), v.end(), std::string(), 
                                            magic_function);
     
        std::cout << sum << '\n'
                  << product << '\n'
                  << magic << '\n';
    }
    
    // transform
    {
        std::string s("hello");
        std::transform(s.begin(), s.end(), s.begin(), std::ptr_fun<int, int>(std::toupper));
        std::cout << s;
    }
}