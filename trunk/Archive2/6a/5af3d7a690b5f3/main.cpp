#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
char* gen = new char[3];
char simp;
char dna[10001];

int main() {
    int len;
    //Reading file and assigning values.
    FILE *input = fopen("input.txt","rt");
    fscanf(input,"%c %c %c %c",&gen[0],&gen[1],&gen[2],&simp);
    fscanf(input,"%s",&dna);
    fclose(input);
    len = strlen(dna);
    //In this part dna has the 2nd line of input.txt
    for(int i=0;i<len;i++){
        cout << dna[i];
    }
    cout << endl;
    //Searching for coincidences.

    int dnaLen = len; //dna Lenght, this one will change over time.
    bool found=false;
    int index=0; //Index will be reseted as well when we make a change!!
    while(index<dnaLen-2) {
            cout << "Entering WHILE with index=" << index << "\n";
            cout << "Examining: " << dna[index] << dna[index+1] << dna[index+2] << endl;
        if(dna[index]=gen[0] && dna[index+1]==gen[1] && dna[index+2]==gen[2]){
            //Replace dna[index] for simp AND displace the dna array
            dna[index]=simp;
            for(int i=0;i<dnaLen;i++){
                cout << dna[i];
            }
            cout << endl;
            index =0;
            dnaLen=dnaLen-2;
        }
        index++;
    }
    return 0;
}