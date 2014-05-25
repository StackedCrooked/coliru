#include <iostream>
#include <string.h>
#include <vector>



bool isInterleaved(char* A, char* B, char* C)
{
    // Find lengths of the two strings
    int M = strlen(A), N = strlen(B);
 
    // Let us create a 2D table to store solutions of
    // subproblems.  C[i][j] will be true if C[0..i+j-1]
    // is an interleaving of A[0..i-1] and B[0..j-1].
    bool IL[M+1][N+1];
 
    memset(IL, 0, sizeof(IL)); // Initialize all values as false.
 
    // C can be an interleaving of A and B only of sum
    // of lengths of A & B is equal to length of C.
    if ((M+N) != strlen(C))
       return false;
 
    // Process all characters of A and B
    for (int i=1; i<=M; ++i)
    {
        for (int j=1 j<=N; ++j)
        {
            std::cout << i+j-1 << std::endl;
        }
    }
    return true;
}

int main ()
{
    isInterleaved("KLM" , "ZMK" , "ZKLMKM");
}