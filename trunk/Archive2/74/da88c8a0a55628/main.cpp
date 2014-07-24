#include <string>

template <typename T>
class SearchableADT
{
public:
    virtual int loadFromFile(string filename) = 0;
    //virtual void clear(void) = 0;
    virtual void insertEntry(T value) = 0;
    virtual void deleteEntry(T value) = 0;
    virtual bool isThere(T value) = 0;
    virtual int numEntries(void) = 0;
};