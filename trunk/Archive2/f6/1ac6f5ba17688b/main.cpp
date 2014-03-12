#include <fstream>
#include <iostream>
#include <random>

int main(int argc, char* argv[])
{
    std::ofstream ofile("out.dat", std::ios::binary);

	std::random_device randDev;
	std::default_random_engine defEngine(randDev());
	std::uniform_int_distribution<int> dist(0, 9);
    auto printSomeNumbers = [&](std::default_random_engine& engine) { for(int i=0; i < 10; i++) { std::cout << dist(engine) << " "; } std::cout << std::endl; };

	std::cout << "Start sequence: " << std::endl;
	printSomeNumbers(defEngine);
	
	ofile << defEngine;
	ofile.close();

	std::default_random_engine fileEngine;

	std::ifstream ifile("out.dat", std::ios::binary);
	ifile >> fileEngine;

	std::cout << "Orig engine: "; printSomeNumbers(defEngine);
	std::cout << "File engine: "; printSomeNumbers(fileEngine);

	std::cin.get();
	return 0;
}