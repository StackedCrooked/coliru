#include<iostream>
#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *fp; int a, b, c;int out;
	fp = fopen("input.txt", "w");
	if (fp == NULL){
		fp = fopen("input.ext", "a+");
		printf("input triples");
		fscanf(fp,"%d%d%d", &a, &b, &c);
       
	}
	fp = fopen("input.txt", "r");
while(out=fgetc(fp)){
    printf("%d",out);
    }
    fclose(fp);
}
