int main(){
  int a[2048], b[2048], c[2048];
  int i;

  for (i=0; i<2048; i++){
      b[i]=0;
      c[i]=0;
  }

  for (i=0; i<2048; i++){
    a[i] = b[i] + c[i];
  }
  
  return a[0];
}