int main()
{
int num[5],i,j,x;

for (i=0;i<=4;i++)
    {
       printf("Por favor informe o numero %d:\n",i+1);
       scanf("%d",&num[i]);
    }

for (i=0;i<=3;i++)
for (j=i+1;j<=4;j++)
if (num[i]>num[j])
{
    x=num[i];
    num[i]=num[j];
    num[j]=x;
}

printf("vetor organizado\n");
for (i=0;i<=3;i++)
{
printf("%d\n",num[i]);
}

return(0);
}