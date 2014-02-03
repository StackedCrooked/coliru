#include <iostream>
#include <sys/time.h>
#include <random>
#include <algorithm>
#include <iterator>

unsigned int naive_log2(unsigned int x)
{
    for (unsigned int i = 32; i > 0; i--) {
		if (x < (1u << i))
			return i;
	}

	return 32;
}

unsigned int clever_log2(unsigned int value)
{
	unsigned int val  = 0;
	unsigned int mask = 0xffff0000;
	unsigned int step = 16;

	while (value) {
		if (value & mask) {
			val += step;
			value &= ~mask;
		}

		step /= 2;

		if (step) {
			mask >>= step;
		} else {
			mask >>= 1;
		}
	}

	return val;
}

unsigned lookup_log2(unsigned int value)
{
	static const unsigned int twos[] = {
		1<<0,  1<<1,  1<<2,  1<<3,  1<<4,  1<<5,  1<<6,  1<<7,
		1<<8,  1<<9,  1<<10, 1<<11, 1<<12, 1<<13, 1<<14, 1<<15,
		1<<16, 1<<17, 1<<18, 1<<19, 1<<20, 1<<21, 1<<22, 1<<23,
		1<<24, 1<<25, 1<<26, 1<<27, 1<<28, 1<<29, 1<<30, 1u<<31
	};

	return std::lower_bound(std::begin(twos), std::end(twos), value) - std::begin(twos);
}

int main()
{
	// generate 10000000 random numbers
	const unsigned int N = 10000000;
	unsigned int *nums = new unsigned int[N];

	volatile unsigned int dummy;
	struct timeval tv0, tv1, tv2, tv3;

    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<> dis(0, 1<<31);

    for (size_t i = 0; i < N; i++) {
		nums[i] = dis(e);
	}

	// time naive approach
	gettimeofday(&tv0, NULL);

	for (size_t i = 0; i < N; i++) {
		dummy = naive_log2(nums[i]);
	}

	// time clever approach
	gettimeofday(&tv1, NULL);

	for (size_t i = 0; i < N; i++) {
		dummy = clever_log2(nums[i]);
	}

	// time lookup table approach
	gettimeofday(&tv2, NULL);

	for (size_t i = 0; i < N; i++) {
		dummy = lookup_log2(nums[i]);
	}

	gettimeofday(&tv3, NULL);

	unsigned long dt_naive  = (tv1.tv_sec * 1000000 + tv1.tv_usec) - (tv0.tv_sec * 1000000 + tv0.tv_usec);
	unsigned long dt_clever = (tv2.tv_sec * 1000000 + tv2.tv_usec) - (tv1.tv_sec * 1000000 + tv1.tv_usec);
	unsigned long dt_lookup = (tv3.tv_sec * 1000000 + tv3.tv_usec) - (tv2.tv_sec * 1000000 + tv2.tv_usec);
	delete[] nums;

	std::cout << "naive:  " << dt_naive  << std::endl
		      << "clever: " << dt_clever << std::endl
		      << "lookup: " << dt_lookup << std::endl;

	return 0;
}
