#include <iostream>

using namespace std;

void quickSort(int A[], int p, int r);
int partition(int A[], int p, int r);

int main(void)
{
    int elements = 8; 
    int number[8] = { 2, 8, 7, 1, 3, 5, 6, 4 };

    int first = 0;
    int last = elements - 1;

    quickSort(number, first, last);

    cout << "Sorted elements: ";

    for (int i = 0; i < elements; i++)
    {
        cout << number[i] << " ";
    }

    cout << endl;

    return 0;

}

void quickSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q= 0;
        q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

int partition(int A[], int p, int r)
{
    int temp;

    int x = A[r];
    int i = p - 1;
    for (int j = i+1; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
    }

    temp = A[r];
    A[r] = A[i + 1];
    A[i + 1] = temp;

    return (i+1);
}