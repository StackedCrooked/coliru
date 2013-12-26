#include <iostream>
#include <vector>
using namespace std;
 
struct int24_t {
        private: char nums[3];
 
        public:
 
        int24_t(int32_t i) {
                nums[0] = (i >> 16) & 0xFF;
                nums[1] = (i >> 8) & 0xFF;
                nums[2] = i & 0xFF;
        }
 
        operator int32_t() {
                return (nums[0] << 16) | (nums[1] << 8) | nums[2];
        }
};
 
int main(int argc, char* argv[]) {
    const size_t NUM_ELEMENTS = 5;
    std::vector<int24_t> v(NUM_ELEMENTS, 0);
    cout << ((long)(&v[NUM_ELEMENTS-1]+1) - (long)&v[0]) << " bytes for " << NUM_ELEMENTS << " elements\n";
}