#include <iostream>

#include <stdint.h>

 

template<uint64_t N, uint64_t M>

struct NWD

{

static constexpr uint64_t value = NWD<M, N % M>::value;

};

 

template<uint64_t N>

struct NWD<N, 0>

{

static constexpr uint64_t value = N;

};

 

template<uint64_t...>

struct NWW

{

};

 

template<uint64_t N, uint64_t M>

struct NWW<N, M>

{

static constexpr uint64_t value = (N * M) / NWD<N, M>::value;

};

 

template<uint64_t N, uint64_t... rest>

struct NWW<N, rest...>

{

static constexpr uint64_t value = NWW<N, NWW<rest...>::value>::value;

};

 

int main()

{

std::cout << NWW<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>::value << std::endl;

}