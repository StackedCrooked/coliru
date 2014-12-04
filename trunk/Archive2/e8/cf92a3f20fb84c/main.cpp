#include <iostream>
#include <ctime>
#include <boost/random.hpp>
#include "boost/random/mersenne_twister.hpp"


typedef boost::mt19937 rng_t;

// random seeding
int64_t cluster_seedgen(void)
{
int64_t s, seed, pid;
s = time(NULL);
pid = getpid();

seed = abs(((s * 181) * ((pid - 83) * 359)) % 104729);
std::cout << "s " << s << " pid " << pid << " seed " << seed << std::endl;
return seed;
}

rng_t* caffe_rng() {
return static_cast<rng_t*>(new rng_t(cluster_seedgen()));
}

void caffe_rng_gaussian(const int n, const float a, const float sigma, float* r) {
boost::normal_distribution<float> random_distribution(a, sigma);
boost::variate_generator<rng_t*, boost::normal_distribution<float> > variate_generator(caffe_rng(), random_distribution);
for (int i = 0; i < n; ++i) {
r[i] = variate_generator();
}
}

int main()
{
    int nums = 1000;
    float* numbers = new float[nums];
    caffe_rng_gaussian(nums, 0, 0.1,numbers);
    int pos = 0;
    int neg = 0;
    for(int i=0;i<nums;i++)
    {
        //std::cout << numbers[i] << std::endl;
        if (numbers[i] > 0)
            pos++;
        else
            neg++;
    }
    std::cout << "Pos: " << pos << " Neg: " << neg << std::endl;
}
