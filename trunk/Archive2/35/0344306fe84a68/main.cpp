char *Problem5(char chars[], char letter, int *length){
    int newLength=0;
    int counter=0;
    for(int i=0;i<*length;i++){
        if(chars[i]!=letter){
            newLength++;
        }
    }
    int const lll = newLength;
    char newChars[lll];
    for(int x=0;x<*length;x++){
        if(chars[x]!=letter){
            newChars[counter]=chars[x];
            counter++;
        }
    }
    *length=newLength;
    return newChars;
}

int main()
{
    int * length = new int(10);
    char chars2[10] = {'g','g','c','g','a','g','g','g','t','g'};
    char * arrayPointer;
    arrayPointer = Problem5(chars2,'g',length);

    return 0;
}

