#define unused __attribute__((unused))

int main() {
    int *ptr;
    unused int const * const &rptr = ptr;
    //*rptr = 2; //error
    //rptr = nullptr; //error
    
    int arr[1];
    unused int const (&rarr)[1] = arr;
    //rarr[0] = 1; //error
    
    int *ptrarr[1];
    int * const (&rptrarr)[1] = ptrarr;
    *rptrarr[0] = 1;
    
    int const * const (&why)[1] = ptrarr;
}
