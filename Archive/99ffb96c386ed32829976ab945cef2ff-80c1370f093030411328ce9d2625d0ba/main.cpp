#include <boost/type_traits.hpp>

#include <stdlib.h>
#include <list>
#include <ctime>
#include <regex.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

struct Triplet_t {
    char apn[15];
};

const static char apn_filtering_regex[] = "BAYN|BANE";

bool FB_ApnFilteringMatcher(Triplet_t* argTriplet) {

    int32_t error_code;
	regex_t regex_tmp;

	if(argTriplet == NULL || apn_filtering_regex[0] == '\0') {
		return false;
	}

	error_code = regcomp(&regex_tmp, apn_filtering_regex, REG_NOSUB | REG_EXTENDED | REG_ICASE);

	if (error_code == 0) {
		int match;

	      match = regexec(&regex_tmp, argTriplet->apn, 0, NULL, 0);
	      regfree (&regex_tmp);

	      if (match == 0) {
	         return true;
	      }
	}

    return false;
}

int main(int argc, char** argv) {
 
    Triplet_t triplet;
    
    strncpy(triplet.apn, "BAYN", 15);
     
    if(FB_ApnFilteringMatcher(&triplet)) {
        std::cout << "APN Matched, ok!" << std::endl;
    } else {
        std::cout << "APN did not match KO!!!" << std::endl;
    }
    
    strncpy(triplet.apn, "BANE", 15);
     
    if(FB_ApnFilteringMatcher(&triplet)) {
        std::cout << "APN Matched, ok!" << std::endl;
    } else {
        std::cout << "APN did not match KO!!!" << std::endl;
    }
    
    strncpy(triplet.apn, "WANA", 15);
     
    if(FB_ApnFilteringMatcher(&triplet)) {
        std::cout << "APN Matched, KOOOO!" << std::endl;
    } else {
        std::cout << "APN did not match, ok!" << std::endl;
    }
    
    return 0;
}
