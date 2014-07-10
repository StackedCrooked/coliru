#include <iostream>
#include <string>
#include <vector>

std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    int leftSize=left.size();
    int rightSize=right.size();
    int lIter=0, rIter=0;
    std::vector<int> newData;
        
    while (lIter<leftSize||rIter<rightSize)
    {
        if (lIter == leftSize) { while (rIter < rightSize) {newData.push_back(right[rIter++]);std::cout << "M";} }
        else if (rIter == rightSize) { while (lIter < leftSize) {newData.push_back(left[lIter++]);std::cout << "M";} }
        else if (left[lIter] > right[rIter]) {newData.push_back(left[lIter++]);std::cout << "M";}
        else {newData.push_back(right[rIter++]);std::cout << "M";}
    }
    
    return newData;
}

std::vector<int> mergesort(std::vector<int> dataSet)
{
    int dSize=dataSet.size();
    
    std::cout << "Q";
    
    if (dSize == 1) return dataSet;
    
    int pivotElement=dSize/2;
    std::vector<int> left, right, newLeft, newRight, newData;
    for (int i=0; i<pivotElement; i++) {left.push_back(dataSet[i]);}
    for (int i=pivotElement; i<dSize; i++) {right.push_back(dataSet[i]);}
    newLeft=mergesort(left);
    newRight=mergesort(right);
    newData=merge(newLeft, newRight);
    return newData;
}

void quicksort(std::vector<int> *quickData, int startEl, int numEl)
{
    if (numEl<=1) return;
    
    int pivotEl=startEl+(numEl/2);
    int endEl=startEl+numEl;
    
    // Swap end and pivot
    int pivotData=(*quickData)[pivotEl];
    (*quickData)[pivotEl]=(*quickData)[endEl];
    (*quickData)[endEl]=pivotData;
    
    pivotEl=-1;
    int compareData;
    for (int compareEl=startEl; compareEl<endEl; compareEl++)
    {
        compareData=(*quickData)[compareEl];
        
        if (pivotEl != -1 && compareData < pivotData)
        {
            (*quickData)[compareEl]=(*quickData)[pivotEl];
            (*quickData)[pivotEl]=compareData;
            pivotEl=-1;
            std::cout << "P";
        }
        else if (compareData > pivotData)
        {
            pivotEl=compareEl;
            std::cout << "S";
        }
        else {std::cout << "C";}
    }
    
    if (pivotEl != -1)
    {
        (*quickData)[endEl] = (*quickData)[pivotEl];
        (*quickData)[pivotEl] = pivotData;
    } else {pivotEl=endEl;}
    
    quicksort(quickData, startEl, pivotEl-startEl);
    quicksort(quickData, pivotEl, endEl-pivotEl);
}

void printVector(std::vector<int> dataVector)
{
    int dSize=dataVector.size();
    for (int i=0;i<dSize;i++) {std::cout << dataVector[i] << " ";}
    std::cout << std::endl << std::endl;
}

int main()
{
    std::vector<int> data = { 3,9,5,1,8,2,4,7,6 };
    printVector(data);
    
    std::cout << "---- MERGE ----";
    std::vector<int> mergeData=mergesort(data);
    std::cout << std::endl;
    printVector(mergeData);
    
    std::cout << "---- QUICK ----";
    std::vector<int> quickData=data;
    quicksort(&quickData, 0, quickData.size());
    printVector(quickData);
}