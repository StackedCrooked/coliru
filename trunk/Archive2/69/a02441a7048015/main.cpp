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
        int count = children.size();
        archive & count;
        children.resize(count);
        for (int i = 0; i < count; ++i)
        {
            A* ptr = children[i];
            archive & ptr;
            children[i] = ptr;
        }
    }
};


int main()
{
    A* newA = new A();
    newA->someInt = 0;

    A* newPtr = new A();
    newPtr->someInt = 5;
    newPtr->parent = newA;

    newA->children.push_back(newPtr);

    //  Save.
    std::ofstream outputFile("test", std::fstream::out | std::fstream::binary);
    if (outputFile.is_open())
    {
        boost::archive::binary_oarchive outputArchive(outputFile);

        //  Serialize objects.
        outputArchive << newA;
        outputFile.close();
    }

    delete newA;
    delete newPtr;

    A* loadedPtr = nullptr;

    //  Load.
    std::ifstream inputFile("test", std::fstream::binary | std::fstream::in);
    if (inputFile && inputFile.good() && inputFile.is_open())
    {
        boost::archive::binary_iarchive inputArchive(inputFile);

        //  Load objects.
        inputArchive >> loadedPtr;
        inputFile.close();
    }

    assert(loadedPtr);
    assert(loadedPtr->someInt == 0);
    assert(loadedPtr->children.size() == 1);
    assert(loadedPtr == loadedPtr->children[0]->parent);
    assert(loadedPtr->children[0]->someInt == 5);

    return 0;
}
