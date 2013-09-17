#include <sstream>
#include <iostream>
#include <fstream>

bool copyStream(const std::istream& inputStream, std::stringstream& stringStream)
{
    if(inputStream)
    {
        std::copy(std::istreambuf_iterator<char>(inputStream.rdbuf()),
                  std::istreambuf_iterator<char>(),
                  std::ostreambuf_iterator<char>(stringStream));
        return true;
    }
    
    return false;
}

int main()
{
    std::ifstream ifStream("foo");
	std::stringstream ss;
	copyStream(ifStream, ss);
	
	return 0;
}