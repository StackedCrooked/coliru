#include <boost/multi_array.hpp>
#include <type_traits>
#include <memory>

struct octreenode { int a; int b; };

class world {
public:
    world(double x, double y, double z, int widtheast, int widthnorth, int height)
            : 
                originx(x), originy(y), originz(z), 
                chunkseast(widtheast), chunksnorth(widthnorth), chunksup(height)
    {
#define OPTION 4

#if OPTION == 1
        static_assert(std::is_trivially_destructible<octreenode>::value, "assumption made");
        //std::uninitialized_fill_n(chunk.data(), chunk.num_elements(), octreenode {1, 72});
        std::fill_n(chunk.data(), chunk.num_elements(), octreenode {1, 72});
#elif OPTION == 2
        for(auto a:chunk) for(auto b:a) for(auto&c:b) c = octreenode{1, 72};
#elif OPTION == 3
        for (index cz = 0; cz < chunksnorth; ++cz) {
            for (index cx = 0; cx < chunkseast; ++cx) {
                for (index cy = 0; cy < chunksup; ++cy) {
                    chunk[cz][cx][cy] = octreenode{1, 72};
                }
            }
        }
#elif OPTION == 4
        static_assert(std::is_trivially_destructible<octreenode>::value, "assumption made");
        for (index cz = 0; cz < chunksnorth; ++cz) {
            for (index cx = 0; cx < chunkseast; ++cx) {
                for (index cy = 0; cy < chunksup; ++cy) {
                    new (&chunk[cz][cx][cy]) octreenode{1, 72};
                }
            }
        }
#endif
        (void) originx, (void) originy, (void) originz, (void) chunksup, (void) chunkseast, (void) chunksnorth;
    }

private:
    double originx, originy, originz;
    int chunkseast, chunksnorth, chunksup;

#if 1
    typedef boost::multi_array<octreenode, 3> planetchunkarray; // a boost_multi for chunks
    typedef planetchunkarray::index index;
    planetchunkarray chunk{boost::extents[chunksnorth][chunkseast][chunksup]};
#else
    static_assert(boost::is_trivially_destructible<octreenode>::value, "assumption made");

    std::unique_ptr<octreenode[]> raw { new octreenode[chunksnorth*chunkseast*chunksup] };
    typedef boost::multi_array_ref<octreenode, 3> planetchunkarray;
    typedef planetchunkarray::index index;
    planetchunkarray chunk{raw.get(), boost::extents[chunksnorth][chunkseast][chunksup]};
#endif
};

int main() {
    world w(1,2,3,4,5,6);
}
