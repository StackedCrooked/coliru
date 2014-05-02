#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

// If you want to insert in the front instead, use std::deque
typedef std::vector<unsigned char> BytesContainer;

static void InsertMaskedBytes(BytesContainer& bytes, unsigned digest_value)
{
    for (unsigned i = 0; i < 4; ++i)
	{
		unsigned mask = 0xFF000000 >> (i*8);
		bytes.push_back(digest_value & mask);
	}
}

int main() {
	unsigned const digest_size = 5;
	unsigned digest[digest_size] = {};
	
	BytesContainer bytes;
	
	std::for_each(
		digest,
		digest + digest_size,
		boost::bind(&InsertMaskedBytes, boost::ref(bytes), _1)
		);
		
	return 0;
}