#include <tuple>
#include <iostream>
#include <cmath>
#include <vector>

class FareySeq {
public:
    FareySeq(const int n) : N(n) {}
    std::vector<std::pair<double,double>> GetSequence() const {
        std::vector<std::pair<double, double>> table;  
    
        //Next term Farey sequence
        double x1 = 0;
        double y1 = 1;
        double x2 = 1;
        double y2 = N;
        double x = 1;
        double y = N;
    
        table.push_back( std::pair<double,double>(x2, y2));
        while (y != 1.0) {
            x = std::floor((y1 + N) / y2) * x2 - x1;
            y = std::floor((y1 + N) / y2) * y2 - y1;
            if (x < y && x > 0.1)
                table.push_back( std::pair<double,double>(x, y));
            x1 = x2, x2 = x, y1 = y2, y2 = y;
        }
        return table;
    }
    
private:
    int N;
};

int main(){
    int solution = 0;
    FareySeq f(1000000);
    
    int numerator = 0;
    for (const auto& e : f.GetSequence()) {
        if (e.first == 3 && e.second == 7) {
            solution = numerator;
            break;
        }
        numerator = e.first;
    }
    std::cout << "Solution: " << solution << std::endl;
}