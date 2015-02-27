#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

 // Returns a list containing iterators in random order
   template<class ContainerType>
   std::list<typename ContainerType::const_iterator> getRandomIteratorList(const ContainerType& container)
   {
     typedef typename ContainerType::const_iterator ContainerIterator;

     std::list<ContainerIterator> iteratorList;
     std::vector<ContainerIterator> iteratorVector;
     std::srand(time(0)); 
     typename std::list<ContainerIterator>::iterator listIter;
     int randomPos = 0;
     for (ContainerIterator mapIter = container.begin(); mapIter != container.end(); ++mapIter)
     {
        iteratorVector.push_back(mapIter);
        
        listIter = iteratorList.begin();
        int randValue = rand();

        randomPos = (iteratorList.size() == 0 ? 0 : randValue % iteratorList.size());
        std::cout << randomPos << " | " << iteratorList.size() << " | " << randValue << std::endl;
        for (int i = 0; i < randomPos; ++i)
        {
           ++listIter;
        }

        iteratorList.insert(listIter, mapIter);
     }
     
    random_shuffle(iteratorVector.begin(), iteratorVector.end());
    std::cout << "random_shuffle result :" << std::endl;
    for( auto elem : iteratorVector)
    {
        std::cout << *elem << std::endl;
    }

     return iteratorList;
   }

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::vector<std::string> strings = {"alma", "bela", "cedrus", "duda"};
    
    std::list<std::vector<std::string>::const_iterator> randomizedStrings = getRandomIteratorList(strings);
    
    std::cout << "rand % container.size() result:" << std::endl;
    for( auto elem : randomizedStrings)
    {
        std::cout << *elem << std::endl;
    }
    

}
