#include <stdio.h>
#include <time.h>
#include<algorithm>
#include<vector>
using namespace std;
 
void *LNext(void *p){
    return (int*)p+1;
}
void LSwap(void *p,void *q){
    int a=*(int*)p;
    *(int*)p=*(int*)q;
    *(int*)q=a;
}
bool LLess(void *p,void *q){
    return (*(int*)p^5)<(*(int*)q^5);
}
 
bool myfunction(int i,int j) {  // for std::sort
    return (i^5)<(j^5);
}
 
/****** Start of implementation *****/
 
void *Jump(void *p,int N){
    while(--N>=0) p=LNext(p);
    return p;
}
 
void SwapN(void *A,void *B,int N){
    while(--N>=0){
        LSwap(A,B);
        A=LNext(A);
        B=LNext(B);
    }
}
 
void Merge(void *SA,int LA,void *SB,int LB,void *R){  // possibly SB==Jump(R,LA)
    do{
        while(LLess(SA,SB)){
            LSwap(SA,R);
            SA=LNext(SA); R=LNext(R);
            if(--LA==0){
                if(R!=SB) SwapN(SB,R,LB);
                return;
            }
        }
        LSwap(SB,R);
        SB=LNext(SB); R=LNext(R);
    } while(--LB);
    SwapN(SA,R,LA);
}
 
void MMerge(void *S,void *R,int M,int K){
    int M1=M<<1;
    int K1=K&-M1;
    while(K1){
        void *S1=Jump(S,M);
        Merge(S,M,S1,M,R);
        R=Jump(R,M1);
        S=Jump(S1,M);
        K1-=M1;
    }
    K&=M1-1;
    if(K>M){
        void *S1=Jump(S,M);
        Merge(S,M,S1,K-M,R);
    } else{
        SwapN(S,R,K);
    }
}
 
 
void _print(char *s,void *A,int k){
    long long *a=(long long*)A;
    printf("%s",s);
    for(int i=0;i<k;i++) printf(" %lld",a[i]);
    printf("\n");
}
 
 
 
void *Sort1(void *A,int K,bool side){  // sort some fragment of A, place to A[0]..A[K], return A+K
    if(K==1) return LNext(A);
    void *B=A;
    for(int i=0;i<(K&~1);i+=2){
        void *D=LNext(B);
        if(LLess(D,B)) LSwap(B,D);
        B=LNext(D);
    }
    if(K&1) B=LNext(B);
 
    for(int M=2;M<K;){
        MMerge(A,B,M,K);
        M<<=1;
        if(M>=K){
            if(side) SwapN(A,B,K);
            return B;
        }
        MMerge(B,A,M,K);
        M<<=1;
    }
    if(!side) SwapN(A,B,K);
    return B;
}
 
void ListSort(void *A,int L){
    if(L<=1) return;
    if(L==2){
        void *C=LNext(A);
        if(LLess(C,A)) LSwap(A,C);
        return;
    }
    int K=L>>1;
    void *B=Jump(A,L-2*K);
    void *D=Sort1(B,K,false);
    int L1=L-K;
    while(L1>L/L1){
        K=L1>>1;
        B=Jump(A,L1-2*K);
        void *C=Sort1(B,K,true);
        Merge(B,K,D,L-L1,C);
        L1-=K;
        D=C;
    }
    B=A;
    void *E=NULL;
    while(B!=D){
        if(E==NULL){
            E=B;
            for(void *C=LNext(B);C!=D;C=LNext(C)){
                if(LLess(C,E)) E=C;
            }
        }
        if(L1!=L && LLess(D,E)){
            LSwap(B,D);
            if(B==E) E=D;
            D=LNext(D);
            L1++;
        } else{
            LSwap(B,E);
            E=NULL;
        }
        B=LNext(B);
    }
}
 
/****** End of implementation *****/
 
int LEN=9999847;
int *A=new int[LEN];
int rnd=12345678;
int GenArray(int N){
    int r=rnd;
    for(int q=0;q<N;q++){
        A[q]=r=r*199973+1;
    }
    return N;
}
 
bool TestSort(void(*srt)(int *arr,int n),int N,char *name){
    GenArray(N);
    long t1=clock();
    (*srt)(A,N);
    long t2=clock();
    bool q=true;
    for(int i=1;i<N;i++){
        if(myfunction(A[i],A[i-1])) q=false;
    }
    printf("%s: %s, time=%ld\n",name,q ? "Ok" : "Fail",t2-t1);
    return q;
}
 
void _ListSort(int *arr,int len){
    ListSort((void*)arr,len);
}
void qsortstd(int *arr,int len){
    std::sort(arr,arr+len,[](int i, int j){ return (i^5)<(j^5); }/*myfunction*/);
}
 
 
int main(){
    for(int K=4;K>=0;K--){
        int N=LEN>>K;
        printf("N=%d\n",N);
        TestSort(_ListSort,N,"ListSort");
        TestSort(qsortstd,N,"std::sort");
    }
}