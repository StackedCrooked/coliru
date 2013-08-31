#include <stdio.h>

/* 
* Bubble Sort
* O(n^2)
*/
void bubbleSort(int a[], int n){
  int i, j, temp;

  for (i = (n - 1); i >= 0; i--){
    for (j = 1; j <= i; j++){
      if (a[j-1] > a[j]){
        temp = a[j-1];
        a[j-1] = a[j];
        a[j] = temp;
      }
    }
  }
}

// selection sort
// best case:    	O(n^2)
// avrg case:		O(n^2)
// worst case:		O(n^2)
void selection_sort(int a[], int n){
  int i, j;
  int min, temp;

  for (i = 0; i < n-1; i++){
    min = i;
    for (j = i+1; j < n; j++){
      if (a[j] < a[min])
        min = j;
    }
    temp = a[i];
    a[i] = a[min];
    a[min] = temp;
  }
}

// insertion_sort
// best case:		O(n)
// avrg case:		O(n^2)
// worst case:		O(n^2)
void insertion_sort(int a[], int n){
    int i, j, index;
    
    for (i = 1; i < n; i++){
        index = a[i];
        j = i;
        while ((j>0)&&(a[j-1] > index)){
            a[j]=a[j-1];
            j=j-1;
        }
        a[j]=index;
    }
}

/*
*	Heap Sort
*/

void siftDown(int a[], int root, int bottom){
    int done, maxChild, temp;

	done = 0;
	while ((root*2 <= bottom) && (!done)){
		if (root*2 == bottom)
			maxChild = root * 2;
		else if (a[root * 2] > a[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;

		if (a[root] < a[maxChild]){
			temp = a[root];
			a[root] = a[maxChild];
			a[maxChild] = temp;
			root = maxChild;
		}
		else
		done = 1;
	}
}

void heap_sort(int a[], int n){
	int i, temp;

	for (i = (n / 2)-1; i >= 0; i--)
		siftDown(a, i, n);

	for (i = n-1; i >= 1; i--){
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		siftDown(a, 0, i-1);
	}
}

void print_result(int a[], int n){
    int i=0;
    for(; i<n;i++)
        printf("%d ", a[i]);
    printf("\n");
}


int main () {
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int b[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    insertion_sort(b, n);
    print_result(b, n);
    
    heap_sort(a, n);
    print_result(a, n);

    
    return 0;
}
 