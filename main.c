#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>


void *dead_check_bonus(void *ptr) {
    printf("hajox\n");
    return (0);
}

int main() {
    // int a = 5;
    // sem_t *sem;
    // sem_unlink("/sem");
    // sem = sem_open("/sem", O_CREAT, S_IRWXU, 1);
    // fork();
    // printf("%d\n", sem);
    // sem_wait(sem);
    // printf("%d\n", sem);
    // // sem_wait(sem);
    // // printf("%d\n", a);
    // a = 6;
    // sem_post(sem);
    // printf("%d\n", a);
	pthread_create(NULL, NULL, &dead_check_bonus, NULL);


    printf("barev\n");
    // sem_post(sem);
    return (0);
}