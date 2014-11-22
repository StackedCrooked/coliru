#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

int _calculatePoints(int n){
    if (n < 58 && n > 47){
        return n-48; // 0 worth 0
    }
    else if (n > 64 && n < 91){
        return n-64; // A worth 1
    }
    else if (n > 96 && n <123){
        return n-96; // a worth 1
    }
    else{
        return 0;
    }
}
// Private Malloc with Assert
void * _malloc(int size)
{
    void *ptr = malloc(size);
    assert(ptr != NULL);
    return ptr;
}


/**/
char* SumCharsAndDigits(const char* str){
    int c=0; // count
    int sum = 0; // Sum of Chars and Digits
    while(str[c]){
        sum += _calculatePoints(str[c]);
        c++;
    }
    while(sum>9){
        int sum2 = sum;
        sum = 0;
        while (sum2%10 > 0){
            sum += sum2%10;
            sum2 = sum2/10;
        }
    }
    char * ret = (char*)_malloc(sizeof(char));
    *ret = (char)sum;
    return ret;
}

char * _copy(const char * str, int begin, int end){
   size_t size = (end-begin);
   char * ret = (char*)_malloc(sizeof(char)*size+1);
   memcpy(ret,str+begin,size);
   ret[size] = '\0';
   return ret;
}

typedef struct keyval {
    char * token;
    char * value;
}keyval;

typedef struct keyval_array{
    keyval * array;
    size_t array_size;
    size_t count;
}keyval_array;

keyval * _treatToken(const char * str,int begin,int end){
        char * s = _copy(str,begin,end);
        char * points = SumCharsAndDigits(s);
        keyval * ret = (keyval*)_malloc(sizeof(keyval));
        ret->token = s;
        ret->value = points;
        return ret;
}

void _push(keyval_array* array, keyval* topush){
    if( array->array_size <= array->count ){
        size_t size = array->array_size *2;
        array->array = (keyval*)realloc(array->array,sizeof(keyval)*size);
        assert(array->array != NULL);
        array->array_size = array->array_size*2;
    }
    size_t count =  array->count;
    keyval* myArray = array->array+count;
    myArray->token = topush->token;
    myArray->value = topush->value;
    array->count = array->count++;
}



int compare (const void * a, const void * b)
{
    keyval * k1 = (keyval*) a;
    keyval * k2 = (keyval*) b;
    return *(k1->value) >= *(k2->value);
}


void PrintWordsSorted (const char* str){
    int c = 0;
    int previous = 0;
    keyval_array * k = (keyval_array*)_malloc(sizeof(keyval_array));
    k->array = (keyval*)_malloc(sizeof(keyval));
    k->array_size = 1;
    k->count = 0;
    int k_size;
    while(str[c]){
        if(str[c] == 32){
            _push(k,_treatToken(str,previous,c));
            previous = c+1;
        }
        c++;
    }
    _push(k,_treatToken(str,previous,c));

    qsort(k->array, k->count, sizeof(keyval), compare);
    int i;
    for(i = 0 ; i< k->count;i++){
       keyval current = k->array[i];
       char * s = current.token;
       char * p = current.value;
       printf("\n%d:",*p);
       printf("%s",s);
    }

}


int main()
{

    /*
    Entrée: "123"           => Sortie : "6"
    Entrée: "1d3"           => Sortie : "8"
    Entrée: "1D3"           => Sortie : "8"
    Entrée: "5#83"          => Sortie : "7"  ( 5+0+8+3 = 16 puis 1+6 = 7 )
    */
    printf("%d",*SumCharsAndDigits("123"));
    printf("%d",*SumCharsAndDigits("1d3"));
    printf("%d",*SumCharsAndDigits("1D3"));
    printf("%d",*SumCharsAndDigits("5#83"));
    PrintWordsSorted("Mon code est cool !");
    return 0;
}



