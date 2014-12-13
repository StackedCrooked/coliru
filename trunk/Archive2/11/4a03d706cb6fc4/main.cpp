
   
  int arr={.....}
  sort(arr) //nlogn

  int elem;
  int counter=0;
  for(i=1 to arr.size)//n
  {
      if(arr[i] == arr[i-1])
         counter++;
      else 
      {
          if(counter==k){
              return elem
          }   
         counter=0;
      }
  }

  (n+nlogn)=O(nlogn)
   
