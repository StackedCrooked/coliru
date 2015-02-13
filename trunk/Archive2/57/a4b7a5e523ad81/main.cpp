#include  <iostream>
using namespace std;


int shellSort (int arr[], int a)
{
    
	for (int gap = a / 2; gap > 0; gap /= 2)
	{
		
		for (int i = gap; i < a; i += 1)
		{
			
			int temp = arr[i];

			
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			
			arr[j] = temp;
		}
	}
	return 0;
}

void printArray(int arr[], int a)
{
	for (int i = 0; i<a; i++)
		cout << arr[i] << " ";
}

int main()
{
	int arr[] = { 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16 };


	cout << "Start \n";
	printArray(arr, 16);

	shellSort(arr, 8);

	cout << "\nAfter 8-sort " << endl;
	printArray(arr, 16);

	shellSort(arr, 4);

	cout << "\nAfter 4-sort  " << endl;
	printArray(arr, 16);

	shellSort(arr, 2);

	cout << "\nAfter 2-sort"<<endl;
	printArray(arr, 16);

	shellSort(arr, 1);

	cout << "\nAfter 1-sort" << endl;
	printArray(arr, 16);

	shellSort(arr, 16);

	cout << "\nStop \n";
	printArray(arr, 16);
	cout << endl;


	system("pause");
}



