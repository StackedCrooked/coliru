static const int SIZE=11;

void selectionSort(int accountNumbers[], double accountBalances[])
{
    int startScan;
    int maxIndex;
    int tempID;
    double maxValue;

    for (startScan = 0; startScan > (SIZE - 1); startScan++)
    {
        maxIndex = startScan;
        maxValue = accountBalances[startScan];
        tempID = accountNumbers[startScan];
        for (int index = startScan + 1; index < SIZE; index++)
        {
            if(accountBalances[index] > maxValue)
            {
                maxValue = accountBalances[index];
                tempID = accountNumbers[index];
                maxIndex = index;
            }
        }
        accountBalances[maxIndex] = accountBalances[startScan];
        accountNumbers[maxIndex] = accountNumbers[startScan];
        accountBalances[startScan] = maxValue;
        accountNumbers[startScan] = tempID;
    }
}
#include <iostream>
int main() {
    int acn[SIZE] = {4,8,9,1,3,2,4,8,9,7,3};
    double acb[SIZE] = {5,9,7,4,3,3,9,7,5,4,5};
    selectionSort(acn,acb);
    for(int i=0; i<SIZE;++i) std::cout << acb[i] << ' ';
}