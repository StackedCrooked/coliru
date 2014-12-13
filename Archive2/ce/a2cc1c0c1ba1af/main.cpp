
   
  int arr={.....}
  sort(arr) //nlogn

  int counter=1;
  for(i=1 to arr.size)//n
  {
      if(arr[i] == arr[i-1])
         counter++;
      else 
      {
          if(counter==k){
              return arr[i-1]
          }   
         counter=1;
      }
  }

  (n+nlogn)=O(nlogn)
   
