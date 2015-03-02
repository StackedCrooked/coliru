
#include <vector>
#include <list>
#include <iostream>
#include <utility>

unsigned int asn1_simple_hdr_len(const unsigned char *p, unsigned int len) {
    if (len <= 2 || p[0] > 0x31)
		return 0;
	return (p[1]&0x80) ? (2 + (p[1]&0x7f)) : 2;
}

int main()
{

int seqhdrlen = asn1_simple_hdr_len(p7->data,
    									p7->length);

}