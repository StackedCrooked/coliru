#include <string>
#include <fstream>
#include <iostream>

int main()
{
    std::string path = "file.txt";
	std::fstream fs(path, std::ios::in | std::ios::out | std::ios::trunc);
	fs.write("hello", 5);
	fs.seekp(0, std::ios::beg);
	char buffer[100] = {};
	fs.read(buffer, sizeof(buffer));
	fs.clear(); // clear the expected eof flag
	std::cout << buffer << "\n";
	fs.seekp(1, std::ios::beg);
	fs.write("E", 1);
	fs.seekp(0, std::ios::beg);
	fs.read(buffer, sizeof(buffer));
	std::cout << buffer << "\n";
	return 0;
}
