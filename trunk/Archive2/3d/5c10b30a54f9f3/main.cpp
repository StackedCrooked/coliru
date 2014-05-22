extern int arr[] ;

namespace recursive
{
    int getIndex(int indx){
     
        if(arr[indx] ==-1)
            return 0;
        if(arr[indx]==indx)
            return indx;
        return getIndex(arr[indx]);
    }    
}

namespace iterative
{
    int getIndex(int indx){
     
        while(arr[indx]!=indx  && arr[indx]!=-1){
            indx=arr[indx];
        }
     
            return (arr[indx]==-1?0:indx); //if(arr[indx]==-1) return 0; else return indx;
    }    
}
