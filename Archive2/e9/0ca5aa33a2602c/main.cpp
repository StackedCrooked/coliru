#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>

int shared=0;

typedef  struct aa
{
    int a1;
	int a2;
}aa;

void *add(void * arg)
{
	aa a;
	a=*(aa *)arg;
	shared = (a.a1+a.a2);
	printf("\n\tAddition is:%d",shared);
	pthread_exit(NULL);	
}

void *sub(void * arg)
{
	aa a;
        a=*(aa *)arg;
        shared = (a.a1-a.a2);
        printf("\n\tSubstraction is:%d",shared);
           pthread_exit(NULL);	
}

void *mul(void * arg)
{
       aa a;
       a=*(aa *)arg;
       shared = (a.a1 * a.a2);
       printf("\n\tMul is :%d",shared);
           pthread_exit(NULL);	
}

void *div(void * arg)
{
        aa a;
        a=*(aa *)arg;
        shared = (a.a1 / a.a2);
        printf("\n\tDiv is:%d",shared);
            pthread_exit(NULL);	
}

int main(void )
{
	int ch,r;
	pthread_t th[4];
	aa a3;
	printf("\n enter the two no.");
	scanf("%d %d",&a3.a1,&a3.a2);
	void *msg;
	do
	{
		printf("\n1.addition\n2.Sub\n3.Multiplication\n4.Division\n5.Exit");
		printf("\nEnter the chioce");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				r=pthread_create(&th[0],NULL,add,&a3);
				pthread_join(th[0],&msg);
				printf("\t%s",(char *)msg);
				printf("\t%u",th[0]);
				break;	
		        case 2:
                         	r=pthread_create(&th[1],NULL,sub,&a3);	
			        pthread_join(th[1],&msg);
	                        printf("\t%s",(char *)msg);   		
                                printf("\t%u",th[1]);
       				break;                        
			case 3:
				r=pthread_create(&th[2],NULL,mul,&a3);
				pthread_join(th[2],&msg);
				printf("\t%s",(char *)msg);
				printf("\t%u",th[2]);
				break;
			case 4:
				r=pthread_create(&th[3],NULL,div,&a3);
				pthread_join(th[3],&msg);
				printf("\t%s",(char *)msg);
				printf("\t%u",th[3]);
				break;
			case 5:
				//exit(0);
                break;
		}
		printf("\n do you want to continue...");
		scanf("%d",&ch);
	}while(ch==0);
	return 0;
}
