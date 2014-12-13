
   
  int arr={.....}
  sort(arr) //nlogn
  
  int k=0;
  int elem;
  int counter=0;
  for(i=1 to arr.size)//n
  {
      if(arr[i] == arr[i-1])
         counter++;
      else 
      {
          if(counter>k){
              k=counter  
              elem =arr[i-1];
          }   
         counter=0;
      }
  }
  return k,elem;
  
  (n+nlogn)=O(nlogn)
   
