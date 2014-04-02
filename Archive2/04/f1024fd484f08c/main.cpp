#include <stdio.h>
#include <pthread.h>

int value =0;

void * fct_thr(void * p_data)
{
    while(1)
    {
   
    printf("%d\n",value++);
    }
    
    return NULL;
}



int main()
{
	int i,j;
	int ret;
	pthread_t thr;
	ret = pthread_create (&thr,NULL,fct_thr,NULL);
	if(!ret)
    {
	
	
	for(i=0;i<1000; i++)
	{
        ret ++;
		for(j=0;j<10000;j++);
	}
	
    printf("\n%d", value);
    }
    else printf("threah error");
    while(1) printf("ok");
    return 0;
}