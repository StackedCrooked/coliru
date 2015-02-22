#include <stdio.h>
#include <stdlib.h>
#define GRID_SIZE 20
int main(int argc,char*argv){
    int map[GRID_SIZE][GRID_SIZE]={0};
    int hx=0,hy=0;
    int i,j,remaining=100,c=0;
    for(;remaining--;){
        int f=0;
        c=0;
        for(i=0;i<GRID_SIZE;++i){
            for(j=0;j<GRID_SIZE;++j){
                if(!map[i][j]){
                    ++c;
                    if(((double)rand()/(double)RAND_MAX)<=1./(double)((GRID_SIZE*GRID_SIZE)-remaining-c)){
                        map[i][j]=1;
                        f=1;
                        break;
                    }
                }
            }
            if(f)break;
        }
    }
    int score=0,movement=100;
    const char *msg="You wake up in a dungeon";
    while(movement){
        printf("\033c");
        printf("Movement: %d Score: %d\n",movement,score);
        printf("%s\n",msg);
        for(i=0;i<GRID_SIZE+2;++i)putchar('#');
        putchar('\n');
        for(j=0;j<GRID_SIZE;++j){
            putchar('#');
            for(i=0;i<GRID_SIZE;++i){
                if(hx==i&&hy==j)putchar('@');
                else if(map[i][j])putchar('$');
                else putchar('.');
            }
            putchar('#');
            putchar('\n');
        }
        for(i=0;i<GRID_SIZE+2;++i)putchar('#');
        putchar('\n');
        
        if(map[hx][hy]==1){
            map[hx][hy]=0;
            msg="You found a shiny trinket on the ground. You pick it up. You feel an unweary aura around you.";
            ++score;
            continue;
        }
        
        char move;
        do{
            move=fgetc(stdin);
        }while(move!='w'&&move!='a'&&move!='s'&&move!='d');
        int nx=hx,ny=hy;
        switch(move){
            case 'w':--ny;break;
            case 'a':--nx;break;
            case 's':++ny;break;
            case 'd':++nx;break;
        }
        if(nx<0)nx=0;if(nx>=GRID_SIZE)nx=GRID_SIZE-1;
        if(ny<0)ny=0;if(ny>=GRID_SIZE)ny=GRID_SIZE-1;
        if(nx==hx&&ny==hy){
            msg="You hit the wall! Ow!";
        }else{
            switch(move){
                case 'w':msg="You move North";break;
                case 'a':msg="You move West";break;
                case 's':msg="You move South";break;
                case 'd':msg="You move East";break;
            }
            hx=nx;
            hy=ny;
            --movement;
        }
    }
    printf("\033cAnd then you died.\nYou managed to pick up %d of those cursed trinkets\nbefore you died and your soul went to Hell.\nThis is the goddamn end of the story. Goodbye.\n",score);
}