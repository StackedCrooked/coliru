#include <stdio.h>
#include <stdlib.h>

typedef struct _valueOfWord {
    char * word;
    int value;
} ValueOfWord;

int getValueOfCharAndDigits(const char c){
    if(c >= 'a' && c <= 'z')
        return c - 'a' + 1; /* +1 puisque a doit avoir la valeur 1 */
    if(c >= 'A' && c <= 'Z')
        return c - 'A' + 1; /* +1 puisque a doit avoir la valeur 1 */
    if(c >= '0' && c <= '9')
        return c - '0';
    return -1;
}

int strLen(const char * str){
    int sum;
    for(sum = 0; *str != '\0'; str++){
        sum++;
    }
    return sum;
}

void cpStr(char * res, const char * src){
    int i;
    for(i=0; src[i] != '\0'; i++){
        res[i] = src[i];
    }
    res[i] = '\0';
}

int strLenToNextSpace(const char * str){
    int sum;
    for(sum = 0; *str != ' '; str++){
        sum++;
    }
    return sum;
}

void cpStrToSpace(char * res, const char * src){
    int i;
    for(i=0; src[i] != ' '; i++){
        res[i] = src[i];
    }
    res[i] = '\0';
}

int nbOfWord(const char * str){
    int sum;
    char spaceFlag = 1;
    for(sum = 0; *str != '\0'; str++){
        if(spaceFlag){
            if(*str != ' '){
                sum++;
                spaceFlag = 0;
            }
        }
        else if (*str == ' ')
            spaceFlag = 1;
    }
    return sum;
}
 
void swapElement(ValueOfWord ** tab, int a, int b){
    ValueOfWord * tmp = tab[a];
    tab[a] = tab[b];
    tab[b] = tmp;
}
 
void quickSort(ValueOfWord ** tab, int start, int end){
    ValueOfWord *pivot;
    int pivot_index, chg, i;

    if(end < start)
        return;

    pivot_index = (start + end) / 2;
    pivot = tab[pivot_index];

    swapElement(tab, pivot_index, end);

    for(i = chg = start; i < end; i++){
        if(tab[i]->value < pivot->value){
            swapElement(tab, i, chg);
            chg++;
        }
    }

    swapElement(tab, chg, end);

    quickSort(tab, start, chg - 1);
    quickSort(tab, chg + 1, end);
}

char* SumCharsAndDigits(const char* str){
    int i, sum, value;
    char *tmpResult;

    tmpResult = (char *) malloc((strLen(str)+1) * sizeof(char));
    if(NULL == tmpResult) return NULL;

    cpStr(tmpResult, str);

    do {
        sum = 0;
        for(i = 0; tmpResult[i] != '\0'; i++){
            value = getValueOfCharAndDigits(tmpResult[i]);
            sum += (value < 0 ? 0 : value);
        }
        sprintf(tmpResult, "%d", sum);
    }
    while (sum >= 10);

    return tmpResult;
}

void PrintWordsSorted(const char * str){
    char * tmp = NULL;
    int len, nbWords, i;

    ValueOfWord * element = NULL;
    ValueOfWord ** tab;

    nbWords = nbOfWord(str);

    tab = (ValueOfWord **) malloc(nbWords * sizeof(ValueOfWord*));
    if(NULL == tab) return;

    for(i = 0; i< nbWords; i++){
        len = strLenToNextSpace(str)+1;
        tmp = (char *) malloc(len * sizeof(char));
        if(NULL == tmp) return;

        cpStrToSpace(tmp, str);


        /* We save the word in the tab */
        element = (ValueOfWord *) malloc(sizeof(ValueOfWord));
        if(NULL == element) return;

        element->word = tmp;
        sscanf(SumCharsAndDigits(tmp), "%d", &(element->value));

        tab[i] = element;

        /* we go to the next word */
        str+=len;
    }

    quickSort(tab, 0, nbWords-1);

    for(i = 0; i<nbWords; i++){
        printf("%d: %s\n", tab[i]->value, tab[i]->word);
    }
}

int main(int argc, char ** argv){
    char * res;

    printf("Test de SumCharsAndDigits\n");
    
    res = SumCharsAndDigits("123");
    printf("%s\n", res);
    free(res);

    res = SumCharsAndDigits("1d3");
    printf("%s\n", res);
    free(res);
    
    res = SumCharsAndDigits("1D3");
    printf("%s\n", res);
    free(res);
    
    res = SumCharsAndDigits("5#83");
    printf("%s\n", res);
    free(res);

    printf("\nTest de PrintWordsSorted\n");

    PrintWordsSorted("mon code est cool !");

    return 0;
}