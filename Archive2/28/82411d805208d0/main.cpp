#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <ctime>
#include <stack>
#include <map>
#include <set>
#include <numeric>
#include <cstring>

using namespace std;

//int *inek;//N+1 malloclucan
vector<int> inek;
vector<int> kactane;
vector<int> kactatakildi;
vector<int> mys;
int N;
long long hsnsolve(){
    long long total = 0;
	int cur = 0;
	//vector<int> mys(N,0);
	int lpos = 0;
	mys[(N - 1) - lpos++] = inek[cur];
	while(cur<N-1)
	{
		cur++;
		vector<int>::iterator it = upper_bound(mys.end()-(lpos), mys.end(), inek[cur]);
		int ind = it - mys.begin();
		if (ind != N)
			lpos = (N - 1) - ind + 1;
		else
			lpos = 0;
		total+=lpos;
		mys[(N - 1) - lpos++] = inek[cur];
	}
	return total;
}
long long mfbsolve(){
	long long sum=0;
	//int kactane[N+1],kactatakildi[N+1];
	//memset(kactane,0,N*sizeof(int));
	//vector<int> kactane(N+1,0);
	//vector<int> kactatakildi(N+1);
	inek[N]=2000000000;
	kactatakildi[N-1]=N;
	for(int i=N-2;i>=0;i--){
		for(int j=i+1;j<=N;){
			if(inek[i]>inek[j]){
				kactane[i]+=kactane[j]+1;
				j=kactatakildi[j];
			}
			else{
				kactatakildi[i]=j;
				break;
			}
		}
		sum+=kactane[i];
	}
	return sum;
}
void starttest(){
	clock_t start=clock(),mfbt,hsnt;
	long long mfb=mfbsolve();
	mfbt=clock()-start;
	start=clock();
	long long hsn=hsnsolve();
	hsnt=clock()-start;
	double mfbti,hsnti;
	mfbti=(double)(mfbt)/CLOCKS_PER_SEC*1000.0;
	hsnti=(double)(hsnt)/CLOCKS_PER_SEC*1000.0;
	cout << "(" << mfb << " - " << hsn << "),(" << mfbti << " ms - " << hsnti << " ms)" << endl;
}
void test(int a,int b){
	srand(a*b);
	N=b;
	inek.resize(N+1);
	kactatakildi.resize(N+1);
	for(int i=0;i<a;i++){
		N=(rand()*rand())%b+1;
		//free(inek);
		//inek=(int *)malloc(sizeof(int)*(N+1));
		kactane.assign(N+1,0);
		mys.assign(N,0);
		for(int j=0;j<N;j++){
			inek[j]=(rand()*rand())%1000000000;
		}
		starttest();
	}
}
int main(){
	int a,b;
	cin >> a >> b;
	test(a,b);
	return 0;
}



