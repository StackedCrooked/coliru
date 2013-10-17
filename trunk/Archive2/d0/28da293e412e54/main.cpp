#include <iostream>
#include <stdio.h>

int	main(int argc, char **argv)
{
    if (argc != 2) return 1;
	std::string str(argv[1]);

	tm tm1;

	sscanf(str.c_str(), "%4d%2d%2d-%2d%2d%2d", &tm1.tm_year, &tm1.tm_mon,
           &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

	std::cout << tm1.tm_year << std::endl << tm1.tm_mon << std::endl << tm1.tm_mday << std::endl;
	std::cout << tm1.tm_hour << std::endl << tm1.tm_min << std::endl << tm1.tm_sec  << std::endl;
    
    char outchar[14];
    strftime(outchar, sizeof(outchar), "%Y%m%d-%H%M", &tm1);
    std::cout << outchar << std::endl;
}