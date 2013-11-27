#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <cassert>
#include <fstream>
#include <memory>
#include <vector>

class A
{
public:
    A() {}
    A(const A& rhs) = delete;

    int someInt = 0;
    A* parent = nullptr;
    std::vector<A*> children;

    template <class Archive>
    void serialize(Archive& archive, const unsigned int /* version */)
    {
        archive & someInt;
        archive & parent;
        std::size_t count = children.size();
        archive & count;
        children.resize(count);
        for (std::size_t i = 0; i < count; ++i)
        {
            archive & children[i];
        }
    }
};


int main()
{
    {
        A newA;
        newA.someInt = 13;
    
        A newPtr;
        newPtr.someInt = 42;
    
        newPtr.parent = &newA;
        newA.children.push_back(&newPtr);
    
        //  Save.
        std::ofstream outputFile("test", std::fstream::out | std::fstream::binary);
        if (!outputFile)
            return 1;

        boost::archive::binary_oarchive outputArchive(outputFile);
    
        //  Serialize objects.
        A* tmp = &newA;
        outputArchive << tmp;
        outputFile.close();
    }

    //  Load.
    std::ifstream inputFile("test", std::fstream::binary | std::fstream::in);
    if (!inputFile)
        return 1;

    boost::archive::binary_iarchive inputArchive(inputFile);

    //  Load objects.
    A* loadedPtr = nullptr;
    inputArchive >> loadedPtr;
    inputFile.close();

    assert(loadedPtr);
    assert(loadedPtr->someInt == 13);
    assert(loadedPtr->children.size() == 1);
    assert(loadedPtr == loadedPtr->children[0]->parent);
    assert(loadedPtr->children[0]->someInt == 42);

    std::cout << loadedPtr->children[0]->parent << std::endl;
}
