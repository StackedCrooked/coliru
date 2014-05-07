#include <stdio.h>
#include <stdlib.h>
 
int compare (const void* a, const void* b){  
  return (*(int*)a-*(int*)b);  
}  

int main(void) {  
    int c;
	scanf("%d",&c); 
 
	if(c>=50)
	{
		printf("잘 못된 입력입니다.\n테스트 케이스는 50이하의 숫자만 가능합니다.");
		return -1;
	}
 
	while(c > 0){  
	  int n;
	  int s[100]; //조건에 있었음
	  int count = 0;
 
	scanf("%d",&n); 
	if( 1>n || 100<n )
	{
			printf("잘 못된 입력입니다.\n문자의 개수는 1이상 100이하의 숫자만 가능합니다.");
			return -1;
		}
	  
	  for(int i=0;i<n;i++) 
	  {
	   scanf("%d",s+i);
	   if( 1000 < s[i] )
		{
			printf("잘 못된 입력입니다.\n문자열의 길이는 1000이하의 숫자만 가능합니다.");
			return -1;
		}
	  }
 
	  for(int i=0; i < n; i++){

		qsort (s, n, 4, compare);
		if( i == (n-1) ) 
		{
			break;
		}
		else 
		{
			s[i+1] = s[i]+s[i+1];
			count += s[i+1];
		}
 
	  }
		printf("%d\n",count);
		c--;
	}
	scanf("%d",&c);
	return -1;
}