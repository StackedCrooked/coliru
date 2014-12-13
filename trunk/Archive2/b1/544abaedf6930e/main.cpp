
   
  int arr={.....}
  sort(arr) //nlogn

  int elem;
  int counter=1;
  for(i=1 to arr.size)//n
  {
      if(arr[i] == arr[i-1])
         counter++;
      else 
      {
          if(counter==k){
              return elem
          }   
         counter=1;
      }
  }

  (n+nlogn)=O(nlogn)
   
