// http://stackoverflow.com/questions/25753571/losing-values-in-struct-array-after-leaving-for-loop-in-c

#include <stdio.h>
#include <stdlib.h> 

typedef struct {
    int type;
    int room_number;
    int creat_number;
} creature;

struct room {
    room *north; //refernce to neighbor
    room *south;
    room *east;
    room *west;
    int n,s,e,w;
    int room_name, state;
    creature creature_array[10];
}; 

room * ptr;
 
void addCreature(int rm, int t, int cm) {
    int i = 0;
    int f = 0;
    for (; i < 10; i++) {
        if (ptr[rm].creature_array[i].type != 0||1||2) {
            ptr[rm].creature_array[i].creat_number = cm;
            ptr[rm].creature_array[i].type = t;
            ptr[rm].creature_array[i].room_number = rm;
            break;
        } else {
            f++;
            if (f == 9) {
                printf("Room ");
                printf("%d", ptr[rm].room_name);
                printf(" is full.\n");
            }
        }
    }
}

int main(void) {
    setbuf(stdout, NULL);
    int state, north, south, east, west;
    printf("Welcome!\nHow many rooms?\n");
    int num_r;
    scanf("%d", &num_r);
    ptr = (room *)malloc(num_r * (sizeof (room)));
    int i = 0;
    for (; i < num_r; i++) {
        scanf("%d %d %d %d %d", &state, &north, &south, &east, &west);
        ptr[i].room_name=i;
        ptr[i].state = state;
        ptr[i].n=north;
        ptr[i].s=south;
        ptr[i].e=east;
        ptr[i].w=west;
    }
    printf("How many creatures?\n");
    int room_num, type, creat_num;
    int num_of_c;
    scanf("%d", &num_of_c);
    int p = 0;
    int PC_count = 0;
    int creat_count = 0;
    for (; p < num_of_c; p++) {
        creat_num = creat_count++;
        scanf("%d %d", &type, &room_num);
        if (type == 0) {
            PC_count++;
            if (PC_count > 1) {
                printf("Too many PC players\n");
                exit(0);
            }
            addCreature(room_num,type,creat_num);
            pc = &ptr[room_num].creature_array[p];
        } else {
            addCreature(room_num,type,creat_num);
        }
    }
}
