#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

void Vsemafor(int semafor)
{
    struct sembuf operation;
    operation.sem_num = 0;
    operation.sem_op  = 1;
    operation.sem_flg = 0;
    semop(semafor, &operation, 1);
}

void Psemafor(int semafor)
{
    struct sembuf operation;
    operation.sem_num =  0;
    operation.sem_op  = -1;
    operation.sem_flg =  0;
    semop(semafor, &operation, 1);
}

struct shared_memory {
    int x;
};

enum players {
    first,
    second
};

int main(int argc, char** argv)
{
    int player, shmid, semafor;
    struct shared_memory * sharedMemory;
    if((shmid = shmget(atoi(argv[1]), sizeof(struct shared_memory), IPC_CREAT | IPC_EXCL | 0660)) < 0){
        player = 1;
        shmid = shmget(atoi(argv[1]), sizeof(struct shared_memory), 0660);
    } else {
        player = 0;
    }
    semafor = shmget(atoi(argv[2]), 1, IPC_CREAT | 0600);

    sharedMemory = (struct shared_memory *) shmat(shmid, 0, 0);

    while(1){
        Vsemafor(semafor);
        getchar();
        sharedMemory->x += 10;
        printf("sharedMemory->x : %d\n", sharedMemory->x);
        Psemafor(semafor);
    }
}
