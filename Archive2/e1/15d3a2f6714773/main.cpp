#include <map>
#include <iostream>

class PulseCompare
{
public:
    PulseCompare(int minwidth_):minwidth(minwidth_){};
    bool operator()(const int x, const int y) const {
        return minwidth<(y-x);
    }
private:
    int minwidth;
};


int main()
{
    std::map<int,float,PulseCompare> pulsemap(PulseCompare(256));
    
    pulsemap.insert(std::pair<int,float>(1700,1.0));
    std::cout << "find 1400? " << (pulsemap.find(1400) != pulsemap.end()) << std::endl;
    std::cout << "find 1500? " << (pulsemap.find(1500) != pulsemap.end()) << std::endl;
    std::cout << "find 1600? " << (pulsemap.find(1600) != pulsemap.end()) << std::endl;
    std::cout << "find 1700? " << (pulsemap.find(1700) != pulsemap.end()) << std::endl;
    std::cout << "find 1800? " << (pulsemap.find(1800) != pulsemap.end()) << std::endl;
    std::cout << "find 1900? " << (pulsemap.find(1900) != pulsemap.end()) << std::endl;
    std::cout << "find 2000? " << (pulsemap.find(2000) != pulsemap.end()) << std::endl;
}