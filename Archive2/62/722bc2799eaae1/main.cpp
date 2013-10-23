//
#include    <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define SWAP(x, y) temp = (x); (x) = (y); (y) = temp
#define LT(x, y) ((x) < (y))

int porownaj_C(const void* pm, const void* pn) // funkcja w stylu C
{
    int m = abs(*(int*)pm);
    int n = abs(*(int*)pn);
    if (m < n )  return -1;
    if (m > n)   return 1;
    return 0;
}

void przygotuj(int tab[], int size)
{
    time_t seed = 1000;
    srand(seed);
    for(int i = 0; i < size; i++)
        tab[i] = rand() - RAND_MAX/2;
}

void quick(int arr[], int left, int right)
{
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j)
      {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j)
            {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      if (left < j)
            quick(arr, left, j);
      if (i < right)
            quick(arr, i, right);
}

int comp(const void* a, const void* b)
{
     int *arg1 = (int*)a;
     int *arg2 = (int*)b;

     if (*arg1 < *arg2) return -1;
     else
     if (*arg1 == *arg2) return 0;
     else	return 1;
}

void count(int *A, int size, int range)
{
  int *B = new int[size];
  int *C = new int[range + 1];

  for (int i = 0; i <= range; ++i)
    C[i] = 0;
  for (int i = 0; i < size; ++i)
    ++C[A[i]];
  for (int i = 1; i <= range; ++i)
    C[i] += C[i - 1];
  for (int i = size - 1; i >= 0; --i)
  {
    B[C[A[i]] - 1] = A[i];
    --C[A[i]];
  }

  for (int i = 0; i < size; ++i)
    A[i] = B[i];
  delete[] B;
  delete[] C;
}

void  quicksort (int array[], int lower, int upper)
{
	int temp, pivot, i, m;

	if (lower < upper)
	{
		SWAP(array[lower], array[(upper+lower)/2]);
		pivot = array[lower];
		m = lower;
		for (i = lower + 1; i <= upper; i++)
			if (LT(array[i], pivot))
			{
				m++;
				SWAP(array[m], array[i]);
			}
		SWAP(array[lower], array[m]);
		quicksort (array, lower, m - 1);
		quicksort (array, m + 1, upper);
	}
}

int main()
{
    const int N = 10000000;
    int* tab = new int[N];

    przygotuj(tab, N);
    clock_t c0 = clock();
    qsort(tab, N, sizeof(tab[0]), porownaj_C);
    double t0 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    sort(tab, tab + N);
    double t1 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    quick(tab, 0, N-1);
    double t2 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
	 c0 = clock();
	 count(tab, 0, N-1);
    double t3 = (clock() - c0)/double(CLOCKS_PER_SEC);

     przygotuj(tab, N);
	  c0 = clock();
	  quicksort(tab, 0, N-1);
     double t4 = (clock() - c0)/double(CLOCKS_PER_SEC);

         cout << "qsort : " << t0 << " sekund\n"
    			  << "sort  : " << t1 << " sekund\n"
              << "quick : " << t2 << " sekund\n"
              << "count : " << t3 << " sekund\n"
              << "quicksort : " << t4 << " sekund\n";
    delete [] tab;
}
