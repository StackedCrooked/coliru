#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int ps[1000]={0};
vector<int> indice[1000];
int main() {
  int cases; scanf("%d", &cases);
  for(int j=1;j<=cases;j++) {
    printf("Case #%d: ", j);
    int c, is; scanf("%d%d", &c, &is);
    for(int i=0;i<=c;i++) ps[i]=0;
    for(int i=0;i<=c;i++) indice[i].clear();
    for (int i = 0; i < is; i++) {
      int it; scanf("%d", &it);
      indice[it].push_back(i+1);
      ps[it]=1;
      if (c-it>0&&ps[c-it]) {
        int a, b;
        a = indice[it][0];
        b = indice[c-it][0];
        if(c==2*it&&indice[it].size()>1) {
          b=indice[it][1];
        }

        if (a!=b) {
          printf("%d %d\n", min(a,b),max(a,b));
        }
      }
    }
  }
  return 0;
}