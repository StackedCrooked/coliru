#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
using namespace std;

/**
 * isRunAroundNumbers: check if input is a runaroundnumber.
 */
int helper(int Arr[], int &start, const int size, bool (&CheckArr)[10]){
    int next_num = -1, new_start;

    new_start = start + Arr[start];
    if (start + Arr[start] >= size)
    {
        for (int i = (start+Arr[start])/size; i > 0; i--)
        {

            new_start -= size;
        }
        start = new_start;
    }
    else
    {
        start += Arr[start];
    }
    next_num = Arr[start];

    for (int i = 0; i < 10; i++)
    {
        if (i == next_num)
        {
        if (CheckArr[i])
        {
            next_num = -1;
            break;
        }   
        else
        {
            CheckArr[i] = true;
            break;
        }
        }

    }

    return next_num;
} 
bool isRunAroundNumbers(int input) {
    int start = 0, copy = input, final, num_of_unique;


    // counting number of digits, so I don't have to use a vector
    int counter = 0;
    if (copy < 0) //deals with negative numbers 
    {
        counter = 1;
    }

    while (copy)
    {
        copy /= 10;
        counter ++;
    }

    const int steady_counter  = counter;

    copy = input;
    int NumArr [counter];
    bool CheckArr [10] = {false, false, false, false, false, false, false, false, false , false};
    for (int i = counter; i > 0; i --) // initialize every element of the new array to be -1
    {
        NumArr[i] = -1; // to check later if every digit has been ran through
    }




    while (counter > 0)
    {
        NumArr [counter-1] = copy % 10;
        copy /= 10;
        counter --;     
    }

    counter = steady_counter;

    while (counter > 0)
    {
        final = helper( NumArr, start, steady_counter,  CheckArr);
        if (final == -1)
        {
            return false;
        }

        counter --;

    }

    // count the number of unique digits that have been ran through
    for (int i = 0; i < 10; i++)
    {
        if (CheckArr[i])
        {
            num_of_unique++;
        }
    }

    if ((steady_counter == num_of_unique) & (final == NumArr[0]) )
    {
        return true;
    }
    else
    {

        return false;
    }
}

int main() {}