#include <stdio.h>

/* гистограмма частот встречаемости введенных символов
   подсчитываются символы с ASCII-кодами от 0 до 256 */
main()
{
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
