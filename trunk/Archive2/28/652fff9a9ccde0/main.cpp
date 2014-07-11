#include <map>

class PulseCompare
{
public:
    PulseCompare(int minwidth_):minwidth(minwidth_){};
    bool operator()(const int x, const int y) const {
        if(abs(x-y)>minwidth) return false;
        else return true;
    }
private:
    int minwidth;
};


int main()
{
    std::map<int,float> pulsemap(PulseCompare(256));
}