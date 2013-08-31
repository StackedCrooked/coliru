#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

template<typename K, typename V, typename M>
void moveValueForUniqueKey(M& targetMap, K key, unique_ptr<V>& value) throw(char)
{
    // Check if the key is already in the map
    auto it = targetMap.find(key);
    if (it != targetMap.end())
    {
        throw key;
    }
    else
    {
        targetMap[key] = move(value);
    }
}

int main(int argc, char *argv[])
{
    unordered_map<char, unique_ptr<int> > testMap;
    char key1 = 'A';
    unique_ptr<int> val1(new int(1));

    // Try inserting the first key-value pair
    try
    {
        moveValueForUniqueKey(testMap, key1, (val1));
    }
    catch (char& duplicateKey)
    {
        cerr << "Key '" << duplicateKey << "' already in map." << endl;
    }

    // Print the key-value pairs
    for (pair<const char, unique_ptr<int> >& entry : testMap)
    {
        cout << "testMap['" << entry.first << "'] = " << *entry.second << endl;
    }

    unique_ptr<int> val2(new int(2));

    // Try inserting the key again
    try
    {
        moveValueForUniqueKey(testMap, key1, (val2));
    }
    catch (char& duplicateKey)
    {
        cerr << "Key '" << duplicateKey << "' already in map." << endl;
    }

    // Print the key-value pairs again
    for (pair<const char, unique_ptr<int> >& entry : testMap)
    {
        cout << "testMap['" << entry.first << "'] = " << *entry.second << endl;
    }

    return 0;

}