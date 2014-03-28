#include <stdio.h>
#include <memory.h>

int DD[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
    /* YY[1][2] is february's dates if the year is leap year 
       YY[0][2] is february's dates if the year is not leap year */
 
int dp[2002][13][32][2]; /* size : 1664764 */ 

int y, m, d;
 
bool LEAP(int a){
    if(!(a%400))return true;
    else if((a%100) && !(a%4))return true;
    return false;
}
 
int dy(int yy, int mm, int dd, int w){
    if(dp[yy][mm][dd][w] != -1)return dp[yy][mm][dd][w];
 
    if(yy >= 2001){
        if((mm > 11) || (mm == 11 && dd > 4))return dp[yy][mm][dd][w] = -1;
    }
    
    if(yy == 2001 && mm == 11 && dd == 4)return w;
    
    int py, pm, pd, py2, pm2, pd2;
    
    int x = 0;
    
    if(LEAP(yy))x = 1;
    
    printf("%d %d %d %d\n", yy, mm, dd, w);

 
    /* this year is leap year */
    if(mm < 12 && dd > DD[x][mm+1]){
        py = yy, pm = mm, pd = dd;
        pd++;
        if(DD[x][pm] < pd){
            pd = 1;
            pm++;
        }
        if(pm > 12){
            py++;
            pm = 1;
        }
        return dp[yy][mm][dd][w] = dy(py, pm, pd, !w);
    }else{
        py = py2 = yy, pm = pm2 = mm, pd = pd2 = dd;
        pd++;
        if(DD[x][pm] < pd){
            pd = 1;
            pm++;
        }
        if(pm > 12){
            py++;
            pm = 1;
        } // dy(py, pm, pd, !w);

        pm2++;
        if(pm2 > 12){
            py2++;
            pm2 = 1;
        } // dy(py2, pm2, pd2, !w);

        if(dy(py, pm, pd, !w) != dy(py2, pm2, pd2, !w)){
            if(dy(py, pm, pd, !w) != w)return dp[yy][mm][dd][w] = dy(py, pm, pd, !w);
            else
                return dp[yy][mm][dd][w] = dy(py2, pm2, pd2, !w);
        }else
            return dp[yy][mm][dd][w] = dy(py, pm, pd, !w);
    }
}
 
int main()
{
    int t;
    scanf("%d", &t);
    
    while(t--){
        scanf("%d %d %d", &y, &m, &d);

        memset(dp, 0xff, sizeof(dp));

         /* Adam */

        if(dy(y, m, d, 0) == 1)printf("YES\n");
        else
            printf("NO\n");
    }


}
 
/* The line should contain the answer "YES" or "NO" to the question of whether Adam has a winning strategy against Eve 
   Adam is a first mover. */