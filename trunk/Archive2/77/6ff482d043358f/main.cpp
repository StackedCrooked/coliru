int check()
{
    extern int a[3][3][3];
    for(int i=0; i<3; i++) {
       for(int j=0; j<3; j++) {
           for(int k=0; k<3; k++) {
              int v=a[i][j][k];
              if ( v == 0 ) return 0;
              if ( v == 1 ) goto skip;
           }
       }
       skip: ;
    }
    return 1;
}


int check() {
    int* view = ar;
    auto block = [&](int num) {
        int start = num * 9;
        for (int i = 0; i < 3*3*3; ++i) {
            if (view[i] == 1) return 0;
            if (view[i] == 0) return 1;
        }
        return 0;
    };
    return block(0) || block(1) || block(2);
}