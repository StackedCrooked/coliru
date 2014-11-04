#include <iostream>
#include <fstream>
#include <sstream>

#include <limits>

int main ()
{
    // Simulates a file:
	std::istringstream file(
		"1 John Doe 737\n"
		"1 Lukas Schmidt 487\n"
		"636 Bob Smith 538");

	char arr[3];
	while (file.ignore(std::numeric_limits<std::streamsize>::max(), '\n')
	    && file.seekg(-!file.eof()-sizeof arr, std::ios_base::cur)
	    && file.read(arr, sizeof arr)
	    && file.ignore())
		std::cout.write(arr, 3) << '\n';
}
