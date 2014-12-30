#include <cstdio>
#include <cstdlib>
#define MAX_LENGTH 25
#define NUM_STRINGS 50
#define HASH_SIZE 65536 //2^16
#define MAX_TRIAL 10
unsigned long hash(const char*str){unsigned long h=5381,c;while((c=*str++))h=((h<<5)+h)+c;return h%HASH_SIZE;}
char strings[NUM_STRINGS][MAX_LENGTH+1];
int hashes[NUM_STRINGS];
void generate_random_strings(void){
    int i,j;
    for(i=0;i<NUM_STRINGS;++i){
        int string_length=rand()%MAX_LENGTH;
        for(j=0;j<string_length;++j){
            strings[i][j]=rand()%26+'A';
        }
        strings[i][j]='\0';
    }
}
int compare(const void*a,const void*b){
    int*ia=(int*)a,*ib=(int*)b;
    return *ia-*ib;
}
void compute_hashes(void){
    int i;
    for(i=0;i<NUM_STRINGS;++i)hashes[i]=hash(strings[i]);
    qsort(hashes,sizeof(hashes)/sizeof(*hashes),sizeof(*hashes),compare);
}
int count_collisions(void){
    int i,num_collisions=0;
    for(i=1;i<NUM_STRINGS;++i){
        if(hashes[i]==hashes[i-1])++num_collisions;
    }
    return num_collisions;
}
int main(){
    int cur_trial,i,total_collisions=0;
    for(cur_trial=0;cur_trial<MAX_TRIAL;++cur_trial){
        generate_random_strings();
        compute_hashes();
        printf("Hashes: ");
        for(i=0;i<NUM_STRINGS;++i)printf("%d;",hashes[i]);
        printf("\n");
        int num_collisions=count_collisions();
        total_collisions+=num_collisions;
        printf("Number of collisions: %d\n",num_collisions);
    }
    printf("Average number of collisions: %.4f\n",(double)total_collisions/(double)MAX_TRIAL);
    return 0;
}
