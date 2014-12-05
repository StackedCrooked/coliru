


int sum(long...);

int main()
{
    return sum(1)                         // edi
         + sum(1, 2)                      // edi, esi
         + sum(1, 2, 3)                   // edi, esi, edx
         + sum(1, 2, 3, 4)                // edi, esi, edx, ecx
         + sum(1, 2, 3, 4, 5)             // edi, esi, edx, ecx, r8d
         + sum(1, 2, 3, 4, 5, 6)          // edi, esi, edx, ecx, r8d, r9d
         + sum(1, 2, 3, 4, 5, 6, 7)       // edi, esi, edx, ecx, r8d, r9d, push
         + sum(1, 2, 3, 4, 5, 6, 7, 8)    // edi, esi, edx, ecx, r8d, r9d, push, push
         + sum(1, 2, 3, 4, 5, 6, 7, 8, 9) // edi, esi, edx, ecx, r8d, r9d, push, push, push
         ;
}