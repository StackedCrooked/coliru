#include <iostream>
#include <string>
#include <vector>
#include <cmath>

bool tbb::localSearch(Dir map[ROWS][COLS], Dir map2[ROWS][COLS],int r, int c, SitRep sitrep){
    if(map[r][c]!=none)return false;
    if(sitrep.thing[r][c].what==rock)return false;

    if(r-1>=0  &&map2[r-1][c  ]!=none){map[r][c]=up;return true;}
    if(c+1<COLS&&map2[r  ][c+1]!=none){map[r][c]=rt;return true;}
    if(r+1<ROWS&&map2[r+1][c  ]!=none){map[r][c]=dn;return true;}
    if(c-1>=0  &&map2[r  ][c-1]!=none){map[r][c]=lt;return true;}

    return false;
}
Dir tbb::pathDirFor(int sr, int sc, int er, int ec,SitRep sitrep){
    Dir map[ROWS][COLS],map2[ROWS][COLS];

    int i,j;
    bool changes=true;

    for(i=0;i<ROWS;++i){
        for(j=0;j<COLS;++j){
            map[i][j]=none;
            map2[i][j]=none;
        }
    }
    map[er][ec]=rt;
    map2[er][ec]=rt;


    while(changes){
        changes=false;

        for(i=0;i<ROWS;++i){
            for(j=0;j<COLS;++j){
                if(localSearch(map,map2,i,j,sitrep))changes=true;
            }
        }
        for(i=0;i<ROWS;++i){
            for(j=0;j<COLS;++j){
                map2[i][j]=map[i][j];
            }
        }
    }
    return map[sr][sc];
}
//THIS PART IS IN A DIFFERENT FUNCTION
if(bodyguard){
        //pursuit (MESSY CODE! Bleh...)
        bool somethingToPursue;
        switch(armyDir){
        case rt: somethingToPursue = hostileUnit(crownLoc.r-6,crownLoc.r+6,crownLoc.c,crownLoc.c+6,sitrep,crownLoc);
                 if(somethingToPursue) target=unitWithin(crownLoc.r-6,crownLoc.r+6,crownLoc.c,crownLoc.c+6,sitrep,crownLoc);break;
        case lt: somethingToPursue = hostileUnit(crownLoc.r-6,crownLoc.r+6,crownLoc.c-6,crownLoc.c,sitrep,crownLoc);
                 if(somethingToPursue)target=unitWithin(crownLoc.r-6,crownLoc.r+6,crownLoc.c-6,crownLoc.c,sitrep,crownLoc);break;
        case up: somethingToPursue = hostileUnit(crownLoc.r-6,crownLoc.r,crownLoc.c-6,crownLoc.c+6,sitrep,crownLoc);
                 if(somethingToPursue)target=unitWithin(crownLoc.r-6,crownLoc.r,crownLoc.c-6,crownLoc.c+6,sitrep,crownLoc);break;
        case dn: somethingToPursue = hostileUnit(crownLoc.r,crownLoc.r+6,crownLoc.c-6,crownLoc.c+6,sitrep,crownLoc);
                 if(somethingToPursue)target=unitWithin(crownLoc.r,crownLoc.r+6,crownLoc.c-6,crownLoc.c+6,sitrep,crownLoc);break;
        }

        if(somethingToPursue){
            //Expensive statement
            target.dirFor=pathDirFor(r,c,target.r,target.c,sitrep);
            if(dir==target.dirFor){
                a.action=fwd;
                a.maxDist=1;
                if(rank==knight||rank==crown)a.maxDist=HORSESPEED;
                return a;
            } else {
                a.action=turn;
                a.dir=target.dirFor;
                return a;
            }
        }
    }