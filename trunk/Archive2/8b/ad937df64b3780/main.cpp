 #include <vector>
 #include <iostream>
 #include <functional>
 
 int main()
 {
    std::vector<int> a = { 1,2,3,4,5,6,7,8,9 };
    std::vector<std::reference_wrapper<int>> b(a.begin() + 3, a.begin() + 7);
    for(auto& each : b) {
        each++;
    }
    for(auto& each : a) {
        std::cout << each << "\n";
    }
 }