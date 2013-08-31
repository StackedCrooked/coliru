#include <vector>
#include <unordered_map>

typedef std::unordered_map<int, double> HashMap;

static const int hashTableSize = 17;

int main()
{
    // works fine here
    HashMap objTest(hashTableSize);
    objTest[1] = 1.1; // or objTest.insert({ 1, 1.1 });

    std::vector<HashMap> objHashTable(10, HashMap(hashTableSize));

    // works fine here too
    objHashTable[0].insert({ 1, 1.1 });

    // ZEN achieved; no memory leaks
}
