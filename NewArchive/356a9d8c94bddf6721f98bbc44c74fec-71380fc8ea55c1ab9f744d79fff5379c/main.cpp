
#include <boost/tuple/tuple.hpp>

#include <string>
#include <cstring>
#include <time.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdint.h>

namespace Constraint1 {
typedef enum {
    NONE    		= 0x00000000,
	VAL1			= 0x00000001,
	VAL2			= 0x00000002,
	VAL4			= 0x00000004,
	VAL8			= 0x00000008,
	ALL				= 0xFFFFFFFF
} Type;
}

namespace Constraint2 {
typedef enum {
	NONE			= 0x00000000,
	VAL1			= 0x00000001,
	VAL2			= 0x00000002,
	VAL4			= 0x00000004,
	VAL8			= 0x00000008,
	ALL				= 0xFFFFFFFF
} Type;
}

namespace Constraint3 {
typedef enum {
	NONE			= 0x00000000,
	VAL1			= 0x00000001,
	VAL2			= 0x00000002,
	VAL4			= 0x00000004,
	VAL8			= 0x00000008,
	VAL16			= 0x00000010,
	VAL32			= 0x00000020,
	ALL				= 0xFFFFFFFF
} Type;
}

timespec diff(timespec start, timespec end) {
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

typedef std::vector<boost::tuple<uint32_t, uint32_t, uint32_t> > SettingsConstraintsContainer_t;

int main(int argc, char** argv) {

	double duration = 0;
	std::stringstream ss;
	timespec start,end,result;
	start.tv_sec = 0;
	start.tv_nsec = 0;
	end.tv_sec = 0;
	end.tv_nsec = 0;

	uint32_t to_handle = 0;
	uint32_t test_const1 = Constraint3::VAL1 + Constraint3::VAL2;
	uint32_t test_const2 = Constraint1::VAL1 + Constraint1::VAL2 + Constraint1::VAL8;
	uint32_t test_const3 =  Constraint2::VAL1 +  Constraint2::VAL2 + Constraint2::VAL4;

	SettingsConstraintsContainer_t constraints_;

	SettingsConstraintsContainer_t choosen_;

	constraints_.push_back(boost::make_tuple(Constraint3::VAL1, Constraint1::VAL1, Constraint2::VAL1));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL1, Constraint1::VAL1, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL1, Constraint1::VAL2, Constraint2::VAL1));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL1, Constraint1::VAL2, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL1, Constraint1::VAL4, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL8, Constraint1::VAL1, Constraint2::VAL1));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL8, Constraint1::VAL1, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL8, Constraint1::VAL8, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL8, Constraint1::VAL8, Constraint2::VAL1));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL4, Constraint1::VAL1, Constraint2::VAL2));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL4, Constraint1::VAL1, Constraint2::VAL8));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL2, Constraint1::VAL1, Constraint2::VAL1));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL2, Constraint1::VAL1, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL16, Constraint1::VAL1, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL32, Constraint1::VAL1, Constraint2::VAL4));
	constraints_.push_back(boost::make_tuple(Constraint3::VAL32, Constraint1::VAL2, Constraint2::VAL4));

	clock_gettime(CLOCK_MONOTONIC, &start);

	to_handle = test_const1;

    for(SettingsConstraintsContainer_t::iterator it = constraints_.begin(); it != constraints_.end(); ++it) {
    	if( ( ((*it).get<0>() & to_handle) == (*it).get<0>() ) &&
    			( ((*it).get<1>() & test_const2) == (*it).get<1>() ) &&
    			( ((*it).get<2>() & test_const3) == (*it).get<2>() ) ) {
    		choosen_.push_back((*it));
    		to_handle -= (*it).get<0>();
    	}
    }

    for(SettingsConstraintsContainer_t::iterator it = choosen_.begin(); it != choosen_.end(); ++it) {
    	std::cout << (*it).get<0>() << " " << (*it).get<1>() << " " << (*it).get<2>()<< std::endl;
    }

	clock_gettime(CLOCK_MONOTONIC, &end);
	result = diff(start,end);
	duration = (double)result.tv_nsec/1000000000 + result.tv_sec;
	ss << "Time to process : " << duration
			<< "s"<< std::endl;
	std::cout << ss.str();

    return 0;
}

