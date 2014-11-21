#include <stdio.h>
#include <stdlib.h>

char* SumCharsAndDigits(const char* str);  
void PrintWordsSorted(const char* str);

int main(int argc, char** argv)
{
  const char* chaine1 = "123";
  const char* chaine2 = "1d3";
  const char* chaine3 = "1D3";
  const char* chaine4 = "5#83";
  const char* chaine5 = "coucou";


  char* finale1 = SumCharsAndDigits(chaine1);
  printf("sum for %s is %c:\n",chaine1,*finale1);
  char* finale2 = SumCharsAndDigits(chaine2);
  printf("sum for %s is %c:\n",chaine2,*finale2);
  char* finale3 = SumCharsAndDigits(chaine3);
  printf("sum for %s is %c:\n",chaine3,*finale3);
  char* finale4 = SumCharsAndDigits(chaine4);
  printf("sum for %s is %c:\n",chaine4,*finale4);
  char* finale5 = SumCharsAndDigits(chaine5);
  printf("sum for %s is %c:\n",chaine5,*finale5);


  const char* chaine6 = "mon code est cool !";
  PrintWordsSorted(chaine6);

  return 0;
}

char* SumCharsAndDigits(const char* str)
{
  char* result;
  unsigned int tmp_result =0;

  unsigned int i=0;
  while(*(str+i) !='\0')
    {
      if(*(str+i)>='a' && *(str+i)<='z') 
    {
	  tmp_result = tmp_result + (int)(*(str+i))-'a'+1;
	}
      else if(*(str+i)>='A' && *(str+i)<='Z') 
	{
	  tmp_result = tmp_result + (int)(*(str+i))-'A'+1;
	}
      else if(*(str+i)>='1' && *(str+i)<='9') 
	{
	  tmp_result = tmp_result + (int)(*(str+i))-'1'+1;
	}
      i++;
    }

  
  while(tmp_result/10 != 0)
    {
      tmp_result = tmp_result/10 + tmp_result%10;
    }

  if(tmp_result > 9)
    {
      result = SumCharsAndDigits(result);
    }

  result = (char*)calloc(1,sizeof(char));
  *result = (char)(tmp_result+'0');

  return result;
}
void PrintWordsSorted(const char* str)
{

  char** result;
  result = (char**)calloc(1,sizeof(char*));
  *result = (char*)calloc(1,sizeof(char));

  unsigned int i=0;
  unsigned int last=0;
  unsigned int wcount=0;
  while(*(str+i) !='\0')
    {
      if(*(str+i) == ' ')
	{
	  unsigned int j=0;
	  wcount++;
	  result = (char**)realloc(result,wcount*sizeof(char*));
	  //*(result+wcount) = (char*)calloc(i-last,sizeof(char));
	  for(j=0;j<i;j++)
	    {
	      
	      printf("%c",*(str+j));
	    }
	  printf("\n");
	  last = i;
	}
      i++;
    }

  printf(" --------------- sorting words -----------------\n");
  printf("%s\n",*result);

  //free memory
  unsigned int k=0; 
  for(k=0; k<wcount;k++)
    {
      free(*(result+i));
    }
  free(result);

}
