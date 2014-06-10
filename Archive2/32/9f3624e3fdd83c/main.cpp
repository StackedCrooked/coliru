#include <stdio.h>
 
int main(void)
{
    
    char buffer[BUFSIZ];
    FILE * fp = fopen("eadsadasd.txt","w+");
    setbuf(fp,buffer);
 
    /* Exhibit the contents of buffer. */
    fputs ("waoooo ",fp);
    printf("%s\n", buffer);
    
 
    fclose(fp);
 
    return 0;
}