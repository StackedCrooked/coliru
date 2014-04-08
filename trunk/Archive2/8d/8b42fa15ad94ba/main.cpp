#include <functional>
#include <algorithm>


int main() {
    const int sampleSize = 10;
    float spec[sampleSize] = {};
    float maxVol = 1.0;
        
    {
        struct percent_of {
            //that lambda captures maxVol by copy when constructed
            percent_of(float maxVol) : maxVol(maxVol) {} 
            //the lambda takes a "float dB" and returns a float
            float operator()(float dB) const { return dB / maxVol; }
        private:
            float maxVol;
        };
    
        if (maxVol != 0)
            std::transform(&spec[0], &spec[sampleSize], &spec[0], percent_of(maxVol));
    }
    {
    
        if (maxVol != 0) {
            using std::placeholders::_1;
            auto percent_of = std::bind(std::divides<float>(), _1, maxVol);
            std::transform(&spec[0], &spec[sampleSize], &spec[0], percent_of);
        }
        
    }
}