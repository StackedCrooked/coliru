#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* SumCharsAndDigits(const char* string);
void PrintWordsSorted(const char* toSort);
int CharToNum(char c);
int CountWord(const char* s);
int CountChar(const char* s);

void tri_a_bulle(int* t, int const size,char** t2) 
{
    int en_desordre = 1;
    int i,j;
     
    for (i = 0; (i < size) && en_desordre; ++i)
    {
        en_desordre = 0;
        for (j = 1; j < (size - i); ++j)
        {
            if (t[j-1] > t[j])
            {
                int temp = t[j-1];
                t[j-1] = t[j];
                t[j] = temp;
                en_desordre = 1;
              }
        }
    }
}
int main(int argc, char** argv)
{
    PrintWordsSorted("mon code est cool !");
    return 0;
}

void PrintWordsSorted(const char* toSort)
{
    int nbWord=CountWord(toSort);
    int i = 0;
    int j =0;
    int nbChar = 0;
    char lastC = toSort[0];
    int* nums = (int*) malloc(sizeof(int)*nbWord);
    char** words = (char**) malloc(sizeof(char*)*nbWord);
    
    while(toSort[i]!= '\0')
    {
        if((toSort[i] == ' ' || toSort[i+1] =='\0') && lastC != ' ')
        {
            if(toSort[i+1] =='\0')
            {
                nbChar++;
            }
            words[j] = (char*) malloc(sizeof(char)*nbChar);
            nbChar=0;
            j++;
        }else if(toSort[i]!=' '){
            nbChar++;
        }
        lastC = toSort[i];
        i++;
    }
    
    bool next = true;
    int count = 0; 
    i = 0; 
    j = 0;
    lastC = toSort[0];
    printf("%c",lastC);
    while(next)
    {
        if((toSort[i] == ' ' || toSort[i] =='\0') && lastC != ' ')
        {
            if(toSort[i] =='\0')
            {
             next = false;
            }
            printf("%s\n",toSort+(i-j));
            
            count++;
            j=0;
        }
        else if(toSort[i]!=' ')
        {
            j++;
        }
        lastC = toSort[i];
        i++;
    }
}

int CountChar(const char* s)
{
    int count = 0;
    int i = 0; 
    while(s[i]!= '\0')
    {
        assert(s[i]!=' ');
        count++;
        i++;
    }
    return count;
}
int CountWord(const char* s)
{
    int count =0;
    int i = 0; 
    char lastC; 
    assert(s[0]!= '\0');
    lastC = s[0];
    while(s[i] != '\0')
    {
        if(s[i] == ' ' && lastC!=' ')
        {   count++;
        }
        lastC = s[i];
        i++;
    }
    if(count > 0 && s[i] !=' ')
    {
        count++;
    }
    return count;
}
char* SumCharsAndDigits(const char* string)
{
    int i = 0;
    int sum = 0;
    char * ret = (char*) malloc(1);

    while(string[i] != '\0')
    {
        sum += CharToNum(string[i]);  
        i++;
    }
    if (sum>9)
    {
        sum%=9;
    }
    char digit = (char) sum;
    ret[0] = digit+'\0';
    return ret;
}

int CharToNum(char c)
{
    if(c<='z' && c >='a')
    {
        return c-'a'+1;
    }else if (c <= 'Z' && c>='A')
    {
        return c-'A'+1;
    }else if(c <='9' && c>='0')
    {
        return c-'0'+1;
    }
    else{
        return 0;
    }
}