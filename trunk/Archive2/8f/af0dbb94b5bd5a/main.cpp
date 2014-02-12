void __attribute__ ((noinline)) mm(                            // Line 3
    int n,
    double*__restrict__ c,
    double*__restrict__ a,
    double*__restrict__ b
) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i + n * j] = 0;                                  // Line 12
            for (k = 0; k < n; k++) {
                c[i + n * j] += a[i + n * k] * b[k + n * j];   // Line 14
            }
        }
    }
}
