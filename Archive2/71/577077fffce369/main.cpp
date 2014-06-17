 #include <vector>
 #include <iostream>
 #include <functional>
 
 int main()
 {
    std::vector<int> a = { 1,2,3,4,5,6,7,8,9 };
    std::for_each(a.begin() + 3, a.begin() + 7, [](int& n){++n;});
    for(auto& each : a) {
        std::cout << each << "\n";
    }
 }