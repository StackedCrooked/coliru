int main() {
    const int vv = 10 ;
    int * p = static_cast<int*>(&vv);
    *p = 5 ; // work well

    const int aa[3] = {11, 12, 13} ;
    int * pp = static_cast<int*>(&aa[1]);

    return 0;
}