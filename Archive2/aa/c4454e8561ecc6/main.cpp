#include <iostream>
#include <functional>
#include <string>
#include <chrono>
#include <cassert>

template <typename F>
float calc(F f) { return -1.0f * f(3.3f) + 666.0f; }

int main() {
    using namespace std::chrono;
    float val1{0}, val2{0};
       {
         const auto tp1 = high_resolution_clock::now();
       for (int i = 0; i < 1e8; ++i) {
          std::function<float(float)> func = [](float arg){ return arg * 0.5f; };
          val2 += calc(func);
       }
       const auto tp2 = high_resolution_clock::now();
       const auto d = duration_cast<milliseconds>(tp2 - tp1);  
       std::cout << "std::function took:" << d.count() << " ms" << std::endl;
   }
   
   
    {
       const auto tp1 = high_resolution_clock::now();
       for (int i = 0; i < 1e8; ++i) {
            auto lambda = [](float arg){ return arg * 0.5f; };
         val1 += calc(lambda);
       }
       const auto tp2 = high_resolution_clock::now();
       const auto d = duration_cast<milliseconds>(tp2 - tp1);  
       std::cout << "lambda took in us :" << d.count() << " ms" << std::endl;
    }  
   assert(val1 == val2);
    return 0;
}