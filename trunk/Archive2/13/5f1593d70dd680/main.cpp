#include <random>

int main(int argc, char* argv[])
{
    const int ActualGridWidth = 1920;
	const int ActualGridHeight = 1080;

	const int MSLevel = 2;
	const int MSGridWidth = ActualGridWidth * MSLevel;
	const int MSGridHeight = ActualGridHeight * MSLevel;

	std::random_device randDev;
	std::default_random_engine randEng(randDev());
	std::uniform_int_distribution<int> dist(0, MSLevel);

	for (auto i = 0; i < ActualGridWidth; i++)
	{
		for (auto j = 0; j < ActualGridHeight; j++)
		{
			// Pick random cell
			auto cellX = i * MSLevel + dist(randEng);
			auto cellY = j * MSLevel + dist(randEng);
			
			// Now compute the ray using MSGridWidth and MSGridHeight
		}
	}
}