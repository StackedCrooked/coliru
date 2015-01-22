#include <emmintrin.h>
#include <cstdio>


union ssereg
{
    unsigned char c[16];
	__m128i v;

	ssereg(int in = 0) : v(_mm_set1_epi32(in)) {}
	ssereg(__m128i in) : v(in) {}

	operator __m128i const&() { return v; }

	void print()
	{
		for(auto byte : c) printf("%02x ", byte);
		puts("");
	}
};




int main()
{
	ssereg a(0x01020304);
	ssereg b(0x05060708);

	ssereg c = _mm_cmplt_epi8(a, b);

	a.print();
	b.print();
	c.print();

    return 0;
}
