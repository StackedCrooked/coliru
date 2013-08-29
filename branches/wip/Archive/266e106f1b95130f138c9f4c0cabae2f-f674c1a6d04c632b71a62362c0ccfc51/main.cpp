#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main()
{
    sem_t *s;
    s = sem_open("probe", O_CREAT, S_IRUSR | S_IWUSR, 0);
    if (s == SEM_FAILED)
    return 0;
    
    int i;
    for(i=0; i< 10; i++) {
        sleep(1);
        sem_post(s);
        printf("%i\n",i);
    }
    
    sem_close(s);
    sem_unlink("probe");
    
    return EXIT_SUCCESS;
    
}