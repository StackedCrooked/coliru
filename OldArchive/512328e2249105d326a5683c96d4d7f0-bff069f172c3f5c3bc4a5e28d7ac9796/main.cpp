#include <vector>
#include <unordered_map>

typedef std::unordered_map<int, double> HashMap;

int main()
{
    // works fine here
    HashMap objTest(17);
    objTest[1] = 1.1; // or objTest.insert({ 1, 1.1 });

    std::vector<HashMap> objHashTable(10, HashMap(17));

    // works fine here too
    objHashTable[0].insert({ 1, 1.1 });

    // ZEN achieved; no memory leaks
}
