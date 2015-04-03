#include <stdio.h>
#include <stdlib.h>

char* StringAlloc (const int size)
{
    /*on alloue size + 1 char pour laisser une place au '\0'*/
    char * str = (char*) calloc (sizeof(char), size + 1);
    if(str == NULL)
    {
        fprintf(stderr, "memory error : cannot allocate a string\n");
        exit(EXIT_FAILURE);
    }
    return str;
}

int ValueOfChar(const char c)
{
    char d = (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
    if(d >= '0' && d <= '9')return (d - '0');
    switch(d)
    {
        case 'a' : case 'j' : case 's' : return 1;
        case 'b' : case 'k' : case 't' : return 2;
        case 'c' : case 'l' : case 'u' : return 3;
        case 'd' : case 'm' : case 'v' : return 4;
        case 'e' : case 'n' : case 'w' : return 5;
        case 'f' : case 'o' : case 'x' : return 6;
        case 'g' : case 'p' : case 'y' : return 7;
        case 'h' : case 'q' : case 'z' : return 8;
        case 'i' : case 'r' : return 9;       
        default: return 0;
    }
    
}

int SumDigits (const int n)
{
    int result = n;
    while(result >= 10)
    {
        result = (result / 10) + (result % 10);
    }
    return result;
}

char* IntToStr (const int n)
{
    int value = n;
    int nb_digit = 1;
    while(value >= 10)
    {
        nb_digit++;
        value = value / 10;
    }
    char* result = StringAlloc (nb_digit);
    
    int index;
    value = n;
    for(index = nb_digit - 1; index >= 0; index --)
    {
        result[index] = (n % 10) + '0';
        index = index / 10;
    }
    return result;
}

char* SumCharsAndDigits(const char* str)
{
    if(str == NULL)
    {
        fprintf(stderr,"argument error : str in SumCharsAndDigits is a NULL pointer\n");
        return NULL;
    }
    int sum = 0;
    int index = 0;
    do
    {
        sum += ValueOfChar(str[index]);
        index++;
    }while(str[index] != '\0');
    sum = SumDigits(sum);
    return IntToStr(sum);
}

int StringToInt(const char* value)
{
    if(value == NULL)
    {
        fprintf(stderr,"argument error : value in StringToInt is a NULL pointer\n");
        return 0; 
    }
    int result = value[0];
    int index = 1;
    while(value[index] != '\0')
    {
        result = result * 10 + (value[index] - '0');
        index++;
    }
    return result;
}

typedef struct __sorted_node__
{
    int ordering_value;
    const char* word;
    __sorted_node__* next;
}Sorted_node, *Sorted_list;

Sorted_list AllocSortedNode(const char* word)
{
    Sorted_list node = (Sorted_list) calloc(sizeof(Sorted_node), 1);
    if(node == NULL)
    {
        fprintf(stderr, "memory error : cannot allocate a sorted_node\n");
        exit(EXIT_FAILURE);
    }
    node -> word = word;
    node -> ordering_value = StringToInt(SumCharsAndDigits(word));
    node -> next = NULL;
    return node;
}

void AddToSortedList(Sorted_list& list, const char* word)
{
    if(list == NULL)
    {
        list = AllocSortedNode(word);
    } else
    {
        Sorted_list tmp = list;
        Sorted_list elt = AllocSortedNode(word);
        while((tmp -> next != NULL) && ((tmp -> next) -> ordering_value <= (elt -> ordering_value)))
        {
            tmp = tmp -> next;
        }
        if((tmp -> next != NULL))
        {
            elt -> next = tmp -> next;
            tmp -> next = elt;
        }else
        {
            tmp -> next = elt;
        }
    }
}

void FreeSortedList(Sorted_list list)
{
    if(list == NULL)return;
    FreeSortedList(list -> next);
    free((void*)list -> word);
    free(list);
}

void PrintWordsSorted(const char* words)
{
    Sorted_list words_list = NULL;
    int index = 0;
    int nw_index = 0;
    int i;
    int current_size;
    char* current_word = NULL;
    
    do
    {
        while(words[nw_index] == ' ')nw_index++;
        if(words[nw_index] == '\0')break;
        index = nw_index;
        while(words[nw_index] != ' ' && (words[nw_index] != '\0'))
        {
            nw_index++;
        }
        current_size = nw_index - index;
        current_word = StringAlloc(current_size);
        for(i = 0; i < current_size; i++)
        {
            current_word[i] = words[index + i];
        }
        AddToSortedList(words_list, current_word);
    }while(words[nw_index] != '\0');
    
    fprintf(stderr, "titi");
    
    Sorted_list tmp = words_list;
    while(tmp != NULL)
    {
        fprintf(stderr,"%d: %s\n", tmp -> ordering_value, tmp -> word);

    }
    fprintf(stderr, "toto");
    FreeSortedList(words_list);
}

int main (int argc, char** argv)
{
    char ex1[] = "123";
    char ex2[] = "1d3";
    char ex3[] = "1D3";
    char ex4[] = "5#83";
    
    char* res1 = SumCharsAndDigits(ex1);
    fprintf(stderr, "for example \"%s\" the result is %s\n", ex1, res1);
    char* res2 = SumCharsAndDigits(ex2);
    fprintf(stderr, "for example \"%s\" the result is %s\n", ex2, res2);
    char* res3 = SumCharsAndDigits(ex3);
    fprintf(stderr, "for example \"%s\" the result is %s\n", ex3, res3);
    char* res4 = SumCharsAndDigits(ex4);
    fprintf(stderr, "for example \"%s\" the result is %s\n", ex4, res4);
    
    char expart2[] = "mon code est cool !";
    PrintWordsSorted(expart2);
    
    free(res1);
    free(res2);
    free(res3);
    free(res4);
    return EXIT_SUCCESS;
}