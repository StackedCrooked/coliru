#include <stdio.h>
 
int main()
{
int num1, num2;
printf("10진수로 된 두개의 숫자 입력: ");
scanf("%d %d",&num1,&num2);
printf("8진수 : 더하기 값 %o 빼기 값 %o 곱하기 값 %o 나누기 값 %o\n", num1+num2,num1-num2,num1*num2,num1/num2);
printf("16진수 : 더하기 값 %x 빼기 값 %x 곱하기 값 %x 나누기 값 %x\n", num1+num2,num1-num2,num1*num2,num1/num2);
return 0;
}