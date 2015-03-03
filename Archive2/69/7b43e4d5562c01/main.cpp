#include <iostream>
#include <boost/cstdint.hpp>

std::string foo(uint32_t IN)
{
    std::string OUT;
    
    // The below is extracted from HARDWARE_VERSION's field definition
    
    // Semtech's algorithm
	uint16_t family     = (IN & 0xFF000000) >> 16;
	uint8_t  generation = (IN & 0x0000FF00) >> 8;
	uint8_t  version    = (IN & 0x000F0000) >> 16;
	
	uint32_t result = family;
	if (generation == 0x02) { // ToPSync 2 - 952x
		result |= 0x0020;
		switch (version) {
			case 8:
				result |= 0x0008;
				break;
			case 4:
				result |= 0x0009;
				break;
			case 3:
				result |= 0x0001;
				break;
			case 2:
				result |= 0x0002;
				break;
			default:
				break;
		}
	}
	
	     if (result == 0x9520) OUT = "ToPSync EVB";
	else if (result == 0x9522) OUT = "SyncBox";
	else if (result == 0x9528) OUT = "SyncPORT";
	else if (result == 0x9529) OUT = "SyncPORT";
	else                       OUT = "ToPSync";
    
    return OUT;
}

int main()
{
    std::cout << "Previously: " << foo(0x95020200) << '\n';
    std::cout << "Currently:  " << foo(0x95020800) << '\n';
    //std::cout << "Properly:   " << foo() << '\n';
}
