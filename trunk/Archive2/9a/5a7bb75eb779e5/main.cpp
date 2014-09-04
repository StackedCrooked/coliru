struct kdnode
{
 kdnode* lch;
 int k;
 void **dataptr;
 kdnode* rch;
}; 
int main(){
kdnode rt;
int k = 10;
rt.dataptr=new void*[k];
rt.dataptr[0]=new int;
*rt.dataptr[0] = 1;
}