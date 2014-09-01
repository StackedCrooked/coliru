#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

/* The direction type is 8 bits, only the first 2 are used */
/* The first 2 bits have the following meanings */
typedef unsigned char direction;
const direction down  = '\x00'; /* 00000000 */
const direction up    = '\x03'; /* 00000011 */
const direction left  = '\x01'; /* 00000001 */
const direction right = '\x02'; /* 00000010 */
/* All other values are interpreted by first zeroing out the last 6 bits */

/* Use to zero out all bits but the last two, also for XORing */
static const direction oneone = '\x03';

inline direction xorflip(const direction d)
{
    /*
	 * XOR with 11
	 * 00 ^ 11 = 11, down  to up
	 * 01 ^ 11 = 10, left  to right
	 * 10 ^ 11 = 01, right to left
	 * 11 ^ 11 = 00, up    to down
	 */
	return d ^ oneone;
}

/* easier to understand flip via switch construct */
/* use this to check the xorflip */
direction switchflip(direction d)
{
	d = d & oneone;
	switch (d)
	{
		case down:  return up;
		case up:    return down;
		case left:  return right;
		case right: return left;
		default:
			std::cerr << "error in switchflip()\n";
			exit(1);
	}
}

std::string dir_str(direction d)
{
	d = d & oneone;
	switch (d)
	{
		case down:  return "down";
		case up:    return "up";
		case left:  return "left";
		case right: return "right";
		default:    return "undefined";
	}
}


void test_flipping(const direction start)
{
	std::cout << "Starting direction is " << dir_str(start) << "\n";
	direction forswitch = start;
	direction forxor    = start;
	std::cout << "Flipping...\n";
	forxor    = xorflip(forxor);
	forswitch = switchflip(forswitch);
	std::cout << "Direction is now " << dir_str(forxor) << "\n";
	assert((forxor & oneone) == (forswitch & oneone));
	std::cout << "Flipping...\n";
	forxor    = xorflip(forxor);
	forswitch = switchflip(forswitch);
	std::cout << "Direction is now " << dir_str(forxor) << "\n";
	assert((forxor & oneone) == (forswitch & oneone));
	std::cout << "Test passed for direction " << dir_str(start) << "\n";
}

int main() {
	test_flipping(down);
	std::cout << std::endl;
	test_flipping(left);
	std::cout << std::endl;
	test_flipping(up);
	std::cout << std::endl;
	test_flipping(right);
	std::cout << std::endl;
	std::cout << "All tests passed\n";
	return 0;
}
