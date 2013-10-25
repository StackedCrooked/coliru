//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define SWAP(x, y) temp = (x); (x) = (y); (y) = temp
#define LT(x, y) ((x) < (y))
#define exch(A, B) {int t = A; A = B; B = t;}
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))

struct porownaj_CPP_fun_obj      // klasa obiektˇw funkcyjnych
{
    bool operator()(int n, int m) const
    {
        return abs(n) < abs(m);
    }
};
//
int porownaj_C(const void* pm, const void* pn) // funkcja w stylu C
{
    int m = abs(*(int*)pm);
    int n = abs(*(int*)pn);
    if (m < n )  return -1;
    if (m > n)   return 1;
    return 0;
}
//
void przygotuj(int tab[], int size)
{
    time_t seed = 1000;
    srand(seed);
    for(int i = 0; i < size; i++)
        tab[i] = rand() - RAND_MAX/2;
}
//
void quick1(int arr[], int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

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
        quick1(arr, left, j);
    if (i < right)
        quick1(arr, i, right);
}
//
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
//
int partition(int a[], int l, int r)
{
    int i = l-1, j = r;
    int v = a[r];
    for (;;)
    {
        while (less(a[++i], v)) ;
        while (less(v, a[--j])) if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}

void quick2(int a[], int l, int r)
{
    int i;
    if (r <= l) return;
    i = partition(a, l, r);
    quick2(a, l, i-1);
    quick2(a, i+1, r);
}
//
void  quick3 (int array[], int lower, int upper)
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
        quick3 (array, lower, m - 1);
        quick3 (array, m + 1, upper);
    }
}
//
void quick4(int a[], int l, int r)
{
    int i, j, k, p, q;
    int v;
    if (r <= l) return;
    v = a[r];
    i = l-1;
    j = r;
    p = l-1;
    q = r;
    for (;;)
    {
        while (less(a[++i], v)) ;
        while (less(v, a[--j])) if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
        if (eq(a[i], v))
        {
            p++;
            exch(a[p], a[i]);
        }
        if (eq(v, a[j]))
        {
            q--;
            exch(a[q], a[j]);
        }
    }
    exch(a[i], a[r]);
    j = i-1;
    i = i+1;
    for (k = l  ; k < p; k++, j--) exch(a[k], a[j]);
    for (k = r-1; k > q; k--, i++) exch(a[k], a[i]);
    quick4(a, l, j);
    quick4(a, i, r);
}
//
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
    sort(tab, tab + N, porownaj_CPP_fun_obj());
    double t1 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    quick1(tab, 0, N-1);
    double t2 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    quick2(tab, 0, N-1);
    double t3 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    quick3(tab, 0, N-1);
    double t4 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    quick4(tab, 0, N-1);
    double t5 = (clock() - c0)/double(CLOCKS_PER_SEC);

    przygotuj(tab, N);
    c0 = clock();
    count(tab, 0, N-1);
    double t6 = (clock() - c0)/double(CLOCKS_PER_SEC);

    cout << "qsort : " << t0 << " sekund\n"
         << "sort  : " << t1 << " sekund\n"
         << "quick1: " << t2 << " sekund\n"
         << "quick2: " << t3 << " sekund\n"
         << "quick3: " << t4 << " sekund\n"
         << "quick4: " << t5 << " sekund\n"
         << "count : " << t6 << " sekund\n";
    // delete [] tab;
}
