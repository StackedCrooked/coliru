#include <iostream>
#include <algorithm>
#include <set>

int presentInBoth(int dest[], int maxDestLength, const int v1[], int v1Length, const int v2[], int v2Length)
{
    std::set<int> destSet;
    for (int v1Index = 0; v1Index < 10; ++v1Index) {
        for (int v2Index = 0; v2Index < 10; ++v2Index) {
            if (v1[v1Index] == v2[v2Index]) {
                destSet.insert(v1[v1Index]);
            }
        }
    }
    
    int destIndex = 0;
    for (int a : destSet) {
        dest[destIndex] = a;
        destIndex++;
    }
    
    return destSet.size();
}

int main()
{
    int vec1[10] = {1, 3, 5, 7, 3, 9, 7, 8, 9, 6};
    int vec2[10] = {1, 5, 3, 10, 15, 11, 7, 20, 91, 11};
    int destVec[10];
    std::cout << "vec1: {1, 3, 5,  7,  3,  9, 7,  8,  9,  6}" << std::endl;
    std::cout << "vec2: {1, 5, 3, 10, 15, 11, 7, 20, 91, 11}" << std::endl;
    int itemsInBoth = presentInBoth(destVec, 10, vec1, 10, vec2, 10);
    std::cout << "Number of items in vec1 and vec2: " << itemsInBoth << std::endl;
    std::cout << "Resulting vec: {";
    for (int index = 0; index < itemsInBoth; ++index) {
        std::cout << destVec[index] << ", ";
    }
    std::cout << "}" << std::endl;
    
    return 0;
}
