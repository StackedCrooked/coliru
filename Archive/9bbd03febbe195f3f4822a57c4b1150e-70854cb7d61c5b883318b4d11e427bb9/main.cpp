#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int SIZE = 10000;
const int MAX = 10000;

auto getRandom()
{
    return rand() % 100;
}

int main()
{
    using namespace std;

    vector<int> myVector;
    int arr[SIZE];
    clock_t start, finish;
    int random;
    for(int i=0; i<SIZE;i++)
    {
        myVector.push_back(0);
        arr[i] = 0;
    }
        //testing for Array
    start = clock();
    for(int i=0; i<MAX;++i)
    {
        random = getRandom(); //returns rand() % 100
        for(int j=0; j<SIZE;++j){
            if(random > arr[j])
            {
                for(int k = SIZE - 1; k > j ; --k)
                {
                    arr[k] = arr[k-1];
                }
                arr[j] = random;
                break;
            }
        }
    }
    //cout << arr[0] << endl;
    finish = clock();
    cout << "Array Time " << finish - start << endl;

    //Vector Processing
    start = clock();
    for(int i=0; i<MAX;++i)
    {
        random = getRandom(); //returns rand() % 100
        for(int j=0; j<SIZE;++j){
            if(random > myVector[j])
            {
                for(int k = SIZE - 1; k > j ; --k)
                {
                    myVector[k] = myVector[k-1];
                }
                myVector[j] = random;
                break;
            }
        }
    }
    finish = clock();
    cout << "Vector Time " << finish - start << endl;
}
