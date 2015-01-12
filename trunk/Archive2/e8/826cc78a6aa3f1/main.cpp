#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <functional>
#include <algorithm>
#include <math.h>

#define FNVHASH(str) ml::hashing::Fnv1aHash(str, strlen(str))

namespace ml
{
    namespace hashing
	{
		const uint32_t Prime = 0x01000193; //   16777619
		const uint32_t Seed  = 0x811C9DC5; // 2166136261

		uint32_t Fnv1aHash(const void* key, unsigned int length)
		{
			uint32_t hash = Seed;
			const unsigned char* ptr = (const unsigned char*)key;
			while (length--)
				hash = (*ptr++ ^ hash) * Prime;
			return hash;
		}
	}
}

float DR(float x, float n, float m) {
    return x - (pow(M_E, (-0.9 * x)) * 100);
    //return (atan(val * rise) * (2 / M_PI) * max);
}

float GetSpeed(float val) {
    val /= 1000.0f;
    return DR(val, 10, 1);
}


void OutputSpeed(float speed) {
   std::cout << speed << " " << GetSpeed(speed) << std::endl;
}


int main()
{
   //uint32_t hsh = FNVHASH("model\\texture\\obj_madaprlightsmall-02.dds");
   //printf("%u", (uint32_t)hsh);
   
   for (int i=1; i<15; ++i) {
        OutputSpeed(i * 1000.0f);
   }
   
   return 0;
}
