#include <iostream>
#include <vector>

void f(const std::vector<std::string>& vec) {
    size_t counter = 1;
    size_t i;
    for(i = 1; i < vec.size(); i++) {
        if(vec[i] == vec[i-1]) 
            counter +=1;
        else  {
            std::cout << vec[i-1] << ", " << counter << std::endl;
            counter = 1;
        }
    }
    std::cout << vec[i-1] << ", " << counter << std::endl;
}

int main() {
    f({"AAA","AAA","AAA","BCA"});
    f({"AAA","AAA","AAA","BCA","BCA"});
    f({"AAA","BCA","BCA"});
    f({"AAA","AAA"});
    f({"AAA"});
    f({});
}