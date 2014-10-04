//
//  main.cpp
//  contest1
//
//  Created by Bekzat Turapbekov on 10/4/14.
//  Copyright (c) 2014 Bekzat Turapbekov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#define tr(con,it) for(typeof(con.begin()) it = con.begin(); it!=con.end();it++)

using namespace std;

int n,b;
int a[10000];
int c[10000];

int main(int argc, const char * argv[]) {
    // insert code here...
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin>>n;
    
    int lastDay = 0;
    
    unordered_set<int> S;
    
    unordered_set<int> Q;
    
    for (int i=0; i<n; i++) {
        cin>>a[i];
    
        S.insert(a[i]);
    }
    
    lastDay = a[n-1];
    
    int t = 0;
    bool ok = 0;
    for (int i=1; i<n; i++) {
        
        if (Q.count(a[i])) {
            continue;
        }
        
        t = a[i]-1;
        ok = 1;
        
        for (int j=1+t+t; j<=lastDay; j+=t) {
            if (!S.count(j)) {
                ok = 0;
                break;
            }
        }
        
        if (ok) {
            for (int j=1+t+t; j<=lastDay; j+=t) {
                Q.insert(j);
            }
        }

    }
    
    int ans = 0;
    for (int i=1; i<n; i++) {
        if (!Q.count(a[i])) {
            ans++;
        }
    }
    
    cout<<ans<<"\n";
    
    return 0;
}
