#include <stdio.h>
#define MAXLINE 1000
 
int getline2(char line[], int lim);
void copy(char to[], char from[]);
 
main()
{
    int len;
    int max;
    int num;
    char line[MAXLINE];
    char longest [MAXLINE];
    
    max = 0;
    num = 0;
    while ((len = getline2(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    
    if (max > 0)
    {
        printf("%s%d\n", longest, max);
    }
    return 0;
}
 
int getline2(char s[], int lim)
{
    int c, i;
    char spike[lim]; /* авторский костыль */
    
 #include <stdio.h>

/* гистограмма частот встречаемости введенных символов
   подсчитываются символы с ASCII-кодами от 0 до 256 */
main(){
    int c, i, j, symbols[256];
    for(i = 0; i < 256; ++i)
        symbols[i] = 0;
  
    while((c = getchar()) != EOF){
        ++symbols[c];
    }
    for(i = 0; i < 256; i++)
        if(symbols[i] > 0){
            if(i >= 32)
                printf("Симв '%c' - ", i);
            else
                printf("Код '%2d' - ", i);
            for(j = 0; j < symbols[i]; ++j)
                putchar('#');
            putchar('\n');
        }
}
