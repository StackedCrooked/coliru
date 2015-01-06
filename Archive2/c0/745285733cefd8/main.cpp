int f(int a(*)[3])
{
    for(int j=0; j<3; j++) {
       for(int k=0; k<3; k++) {
          int v=a[j][k];
          if ( v == 0 ) return 0;
          if ( v == 1 ) return 1;
       }
   }
}

int check()
{
    extern int a[3][3][3];
    for(int i=0; i<3; i++) {
        if(f(a[i] == 0) return 0;
    }
    return 1;
}