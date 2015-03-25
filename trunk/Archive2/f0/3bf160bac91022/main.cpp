#define_REENTRANT
#include<stdio.h>
#include<thread.h>
strut
{
mutex_t data-iock[5];
int int_val[5];
float float_val[5];
}
data;
void*add_to_value();
main()
{
int i:
for(i=0;i<5;i++);
{
mutex_init(&Data.data_lock[i],USYNC_THREAD,0);
Data.int_val[i]=0:
Data.float_val[i]=0;
}
thr_setconcurrency(4);
for(i=0;i<5;i++)
thr_create(NULL,0,Add_to_Value,(void*)(2*i),0,NULL);
for(i=0;i<5;i++)
thr_join(0,0,0);
printf("final Values.....\n");
for(i=0;i<5;i++)
{
printf("integer value[%d]=\t%d\n",i,Data.int_val[i]);
printf("float vale[%d]=\t%.0f\n\n",i,Data.float_val[i]);
}
return(0);
}
void*Add_to_Value(void*arg)
{
int inval=(int)arg;
int i;
for(i=0;i<10000;i++)
{
mutex_iock(&Data.data_lock[i%5]);
Data.int_val[i%5]+=inval;
Data.float_val[i%5]+=(float) 1.5*inval;
mutex_unlock(&Data.data_lock[i%5]);
}
return((void*)0);
}

