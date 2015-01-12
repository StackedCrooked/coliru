#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <map>
#include <bitset>
#include <iostream>
#include <ctype.h>

#define gc getchar  //unlocked linux
#define MOD 1000000007
#define INF numeric_limits<int>::max();
#define FOR(i,v,n) for(i=v;i<n;i++)
#define scan(i) scanf(" %d",&i)
#define scan2(i,j) scanf(" %d %d",&i,&j)
#define scan3(i,j,k) scanf(" %d %d %d",&i,&j,&k)
#define print(i) printf("%d\n",i);
#define pb push_back
#define mk make_pair
#define sz(i) i.size()
#define reset(vec) memset(vec,0,sizeof(vec))
#define ord(vec) sort(vec.begin(),vec.end())
#define rev(vec) reverse(vec.begin(),vec.end())
#define MAX 35

using namespace std;

inline void scanint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

int cmp_double(double a, double b, double eps = 1e-9){
    return a + eps > b ? b + eps > a ? 0 : 1 : -1;  //0 = iguais, 1 = a maior
}

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
// 0 == wall/turret
// 1 == ok
// -1 == laser
int state[110][110][4];
int dp[110][110][4];

// 1 ^ / 2 < / 3 v / 4 >
// 0 wall
// 5 free
// 6 init
// 7 goal
int tab[110][110];
int gX, gY;
int sX, sY;
int L, C;

void filltab(int i, int j, char c){
    if (c=='#') tab[i][j] = 0;
    else if (c=='.') tab[i][j] = 5;
    else if (c=='^') tab[i][j] = 1;
    else if (c=='<') tab[i][j] = 2;
    else if (c=='v') tab[i][j] = 3;
    else if (c=='>') tab[i][j] = 4;
    else if (c=='S') tab[i][j] = 6;
    else if (c=='G') tab[i][j] = 7;
    if (c=='S'){
        sX = j;
        sY = i;
    }
    if (c=='G'){
        gX = j;
        gY = i;
    }
    return;
}

void beam(int i, int j, int dir, int k){
    if (i < 0 || i >= L || j < 0 || j >= C) return;
    if (tab[i][j] >= 5) {
        state[i][j][k] = -1;
        if (dir == UP) beam(i-1, j, dir, k);
        else if (dir == LEFT) beam(i, j-1, dir, k);
        else if (dir == DOWN) beam(i+1, j, dir, k);
        else beam(i, j+1, dir, k);
    }
    return;
}

void turret(int i, int j, int k){
    int dir = tab[i][j]-1;
    dir += k;
    dir %= 4;
    if (dir == UP) beam(i-1, j, dir, k);
    else if (dir == LEFT) beam(i, j-1, dir, k);
    else if (dir == DOWN) beam(i+1, j, dir, k);
    else beam(i, j+1, dir, k);
}

void create_stat(int lin, int col){
    for (int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            if (tab[i][j]>=1 && tab[i][j] <=4){
                for (int k = 0; k < 4; k++)
                    turret(i, j, k);
            }
        }
    }
}

int isFree(int i, int j, int k, int c){
    if (i < 0 || i >= L || j < 0 || j >= C) return 0;
    if (state[i][j][k] == 1 && tab[i][j]>=5){
        if (dp[i][j][k] == -1) {
            dp[i][j][k] = c;
            return 1;
        }else if (dp[i][j][k] > c){ //never
            dp[i][j][k] = c;
            return 1;
        }
        return 0;
    }
    return 0;
}

int main(){
    int t, caso = 1;
    cin >> t;
    while(t--){
        int lin, col;
        cin >> lin >> col;
        L = lin;
        C = col;
        getchar();

        set <pair<pair<int,int> , pair<int,int> > > bag;
        for (int i = 0; i < lin; i++){
            for (int j = 0; j < col; j++){
                char c;
                scanf("%c",&c);
                filltab(i,j,c);
                for (int k = 0; k < 4; k++){
                    dp[i][j][k] = -1;
                    state[i][j][k] = 1;
                }
            }
            getchar();
        }
        create_stat(lin, col);

        dp[sY][sX][0] = 0;
        bag.insert(make_pair(make_pair(0,0),make_pair(sX,sY)));

        while(!bag.empty()){
            pair<pair<int,int>, pair<int,int> > next;
            next = *bag.begin();
            int cust = next.first.first;
            int k = next.first.second;
            int cX = next.second.first;
            int cY = next.second.second;
            bag.erase(bag.begin());
            //printf("unbag x %d, y %d\n",cX,cY);
            if (cX == gX && cY == gY) break;

            k = (k+1) % 4;
            cust++;
            if (isFree(cY-1, cX, k, cust)){
                bag.insert(mk(mk(cust,k), mk(cX, cY-1)));
            }
            if (isFree(cY+1, cX, k, cust)){
                bag.insert(mk(mk(cust,k), mk(cX, cY+1)));
            }
            if (isFree(cY, cX-1, k, cust)){
                bag.insert(mk(mk(cust,k), mk(cX-1, cY)));
            }
            if (isFree(cY, cX+1, k, cust)){
                bag.insert(mk(mk(cust,k), mk(cX+1, cY)));
            }
        }

        bag.clear();
        int ans = -1;
        for (int k = 0; k < 4; k++){
            if (dp[gY][gX][k] == -1) continue;
            if (ans==-1) ans = dp[gY][gX][k];
            else ans = min(dp[gY][gX][k],ans);
        }
        if (ans==-1) printf("Case #%d: impossible\n",caso++);
        else printf("Case #%d: %d\n",caso++, ans);
    }

    return 0;
}
