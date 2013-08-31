#include <iostream>

enum {
    DESC_UNIT	= 12,	// LONG: one of the following values DESC_UNIT_xxx for DTYPE_REAL/DTYPE_VECTOR
	DESC_UNIT_REAL			= 'frea',		//FORMAT_REAL,
	DESC_UNIT_LONG			= 'flng',		//FORMAT_LONG,
	DESC_UNIT_PERCENT		= 'fpct',		//FORMAT_PERCENT,
	DESC_UNIT_DEGREE		= 'fdgr',		//FORMAT_DEGREE,
	DESC_UNIT_METER			= 'fmet',		//FORMAT_METER,
	DESC_UNIT_TIME			= 'ffrm'		//FORMAT_FRAMES,
};

#define X(x) #x ": " << x << "\n"

int main() {
  std::cout << 
    X(DESC_UNIT_REAL) <<
    X(DESC_UNIT_LONG) <<
    X(DESC_UNIT_PERCENT) <<
    X(DESC_UNIT_DEGREE) <<
    X(DESC_UNIT_METER) <<
    X(DESC_UNIT_TIME);
}
