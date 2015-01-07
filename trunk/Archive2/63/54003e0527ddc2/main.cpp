#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>

const unsigned short PERSON_COUNT_MAX = 10;
const unsigned short PERSON_AGE_MAX = 100;
std::size_t personAgeArray[PERSON_COUNT_MAX + 1][PERSON_AGE_MAX + 1];

class AgeRange
{
public:
    
};

class AgeRangePrice
{
public:
    AgeRange ageRange;
    float price;
    
};

class Generator
{
public:
    Generator()
    {
        std::memset(personAgeArray, 0, sizeof(personAgeArray));
    }

    bool insert(unsigned short person, unsigned short ageMin, unsigned short ageMax)
    {
        if (PERSON_COUNT_MAX < person || PERSON_AGE_MAX < ageMin)
            return false;
        const unsigned short personMin = (person == 0 ? 1 : person);
        const unsigned short personMax = (person == 0 ? PERSON_COUNT_MAX : person);
        ageMax = std::min(PERSON_AGE_MAX, ageMax);
        for (unsigned short personIndex = personMin; personIndex <= personMax; ++personIndex)
        {
            for (unsigned short ageIndex = ageMin; ageIndex <= ageMax; ++ageIndex)
            {
                personAgeArray[personIndex][ageIndex] |= static_cast<std::size_t>(1) << counter_;
            }
        }
        ++counter_;
        return true;
    }
    
    void generate()
    {
        for (unsigned short personIndex = 1; personIndex <= PERSON_COUNT_MAX; ++personIndex)
        {
            for (unsigned short ageIndex = 0; ageIndex <= PERSON_AGE_MAX; ++ageIndex)
            {
                if (ageIndex == 2 || ageIndex == 18 || personAgeArray[personIndex][ageIndex - 1] != personAgeArray[personIndex][ageIndex])
                {
                    if (personAgeArray[personIndex][ageIndex - 1] != 0)
                    {
                        std::cout << (ageIndex - 1) << ":" << personAgeArray[personIndex][ageIndex - 1] << "\n";
                    }
                }
            }
        }
    }

private:
    unsigned short counter_;

};

int main(void)
{
	auto start = std::chrono::high_resolution_clock::now();
    
    Generator generator;
    generator.insert(1, 0, 199);
    generator.generate();
    
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms" << std::endl;
	std::cin.get();
}















