#include <fstream>
#include <iostream>
#include <random>

int main(int argc, char* argv[])
{
    std::ofstream ofile("out.dat", std::ios::binary);

	std::random_device randDev;
	std::default_random_engine defEngine(randDev());
	std::uniform_int_distribution<int> dist(0, 9);

	std::cout << "Start sequence: " << std::endl;
	std::cout << dist(defEngine) << " " << dist(defEngine) << " " << dist(defEngine) << std::endl;
	
	ofile << defEngine;
	ofile.close();

	std::default_random_engine fileEngine;

	std::ifstream ifile("out.dat", std::ios::binary);
	ifile >> fileEngine;

	std::cout << "Orig engine: " << dist(defEngine) << " " << dist(defEngine) << std::endl;
	std::cout << "File engine: " << dist(fileEngine) << " " << dist(fileEngine) << std::endl;

	std::cin.get();
	return 0;
}