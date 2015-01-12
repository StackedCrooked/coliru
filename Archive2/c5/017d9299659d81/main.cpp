#include <vector>
#include <algorithm>

struct Auto { virtual int tassa() const { return 123; } };

template<class It>
int calcolaBolli(It begin, It end) {
    return std::accumulate(
        begin, end, 0, 
        [](int c, const Auto* a) {
            return c + a->tassa();
        }
    );
}

int main() {
    std::vector<Auto*> automobili;
    // popola `automobili`
    int bolli = calcolaBolli(automobili.begin(), automobili.end());
}