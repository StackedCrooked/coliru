#include <stdio.h>
 
int main(void)
{
    int file_size;
    char buffer[BUFSIZ];
    FILE * fp = fopen("test.txt","w+");
    setbuf(fp,buffer);
 
    /* Exhibit the contents of buffer. */
    fputs ("aaa",fp);
    printf("%s\n", buffer);
    fputs ("bbb",fp);
    printf("%s\n", buffer);
    fputs ("ccc",fp);
    printf("%s\n", buffer);
    file_size = ftell(fp);
    printf("file_size = %d\n", file_size);
    fflush (fp);              /* flush buffer */
    printf("%s\n", buffer);
    fputs ("ddd",fp);
    printf("%s\n", buffer);
    fputs ("eee",fp);
    printf("%s\n", buffer);
 
    rewind(fp);               /* flush buffer and rewind file */
    char buf[20];
    fgets(buf,sizeof buf,fp);
    printf("%s\n", buf);
 
    fclose(fp);
 
    return 0;
}