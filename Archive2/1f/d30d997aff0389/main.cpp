#include <stdio.h>
 
enum { SIZE = 20 };
int main(void)
{
    FILE *fp = fopen("test.bin", "wb"); // must use binary mode
    fwrite("Q 123 k\r\n",9,1,fp); 
    fwrite("Q 123 k\r\n",9,1,fp); 
    fwrite("Q 123 k\r\n",9,1,fp); 
    fwrite("Q -1234 k\r\n",9,1,fp); 
    fclose(fp);
 
    fp = fopen("test.bin","rb");
    char ch;
    long pos;
    int return_code;
    while ((return_code = fscanf(fp, "Q %l %c\r\n", (long*)(&pos), &ch)) > 0) {
        printf("%d %l %c\r\n", return_code, pos, ch);    
    }
    
}