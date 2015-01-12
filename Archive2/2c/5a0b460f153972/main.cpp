#include <vector>
#include <algorithm>

struct Auto {
    virtual int tassa() const { return 123; }
};
 
class Aci {
private:
    std::vector<const Auto*> Cars;
public:
    
    void aggiungiAuto(const Auto &a) {
        Cars.push_back(&a);
    }
 
    int incassaBolli() const {
        return std::accumulate(Cars.begin(), Cars.end(), 0, [](int c, const Auto* a) {
            return c + a->tassa();
        });
    }
};

int main() {}