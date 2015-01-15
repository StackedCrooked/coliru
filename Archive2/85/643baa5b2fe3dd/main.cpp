#include <boost/multi_array.hpp>

struct octreenode { int a; int b; };

class world {
public:
    world(double x, double y, double z, int widtheast, int widthnorth, int height)
            : 
                originx(x), originy(y), originz(z), 
                chunkseast(widtheast), chunksnorth(widthnorth), chunksup(height)
    {
        octreenode v = { 1, 72 };
        std::fill_n(chunk.data(), chunk.num_elements(), v);
    }

private:
    double originx, originy, originz;
    int chunkseast, chunksnorth, chunksup;

    typedef boost::multi_array<octreenode, 3> planetchunkarray; // a boost_multi for chunks
    typedef planetchunkarray::index index;
    planetchunkarray chunk{boost::extents[chunksnorth][chunkseast][chunksup]};
};

int main() {
    world w(1,2,3,4,5,6);
}
