#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std; 

void fill(int arr[], int size, int minNum, int maxNum) 
{
  srand(time(0));
  
  for (int i = 0; i < size; i++) {
    
    arr[i] = rand()%maxNum + minNum;
  }
}

void print(const int arr[], int size)
{
  for (int i = 0; i < size; i++) {
    
    cout << '[' << i << "] = " << arr[i] << '\n';
  }
}

///////////////// JUST SO ITS EASIER TO PLAY WITH ////////////////////////
///////////////// JUST SO ITS EASIER TO PLAY WITH ////////////////////////
///////////////// JUST SO ITS EASIER TO PLAY WITH ////////////////////////
///////////////// JUST SO ITS EASIER TO PLAY WITH ////////////////////////



int search(int data[], int size, int lefty, int righty, int key)
{
  //calculate midpoints
  int left = lefty + (righty - lefty) * 1/3;
  int right = lefty + (righty - lefty) * 2/3;
  
  cout << left << " and " << right << '\n';
  
  //check midpoints for occurrences of the key, return index value
  if (key == data[left]) {
    
    return left;
  }

  else if (key == data[right]) {
    
    return right;
  }
  
  //if no occurences exist, return -1
  else if (left <= 0 || left > right || right > 29) {
    
    return -1;
  }
  
  else if (key > data[left] && key < data[right]) {
    cout << left << "+1 and " << right << "-1\n";
      
    return search(data, size, left+1, right-1, key);
  }

  else if (key < data[left]) {
    cout << left << "-1\n";
      
    return search(data, size, left-1, right, key);
  }

  //  1, 2, [3]++
  else if (key > data[right]) {
    cout << right << "+1\n";
      
    return search(data, size, left, right+1, key);
  }
}

int main()
{
  int key;
  int index;
  int size;
  int data[30];
  
  //set size
  size = 30;
  
  //populate data
  fill(data, size, 1, 10);

  //sort data
  sort(data, data+size);

  key = 8;

  //print data for visual feedback
  print(data, size);
  
  cout << left << " and " << right << '\n';
  
  //search data and output index
  index = search(data, size, 0, 29, key);

  
  return 0;
}
