#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int Gv;
int n;

sem_t sem;

void *thread()
{
    for (int i = 0; i < n; i++)
    {
        // sem_wait decrements the semaphore
        // sem_wait(sem_t *sem);
        // Parameters:
        // 1º - sem_t *sem -> The semaphore
        // Return value: 0 if successful, otherwise -1
        sem_wait(&sem);

        Gv -= 1;

        // sem_post increments the semaphore
        // sem_post(sem_t *sem);
        // Parameters:
        // 1º - sem_t *sem -> The semaphore
        // Return value: 0 if successful, otherwise -1
        sem_post(&sem);
    }
}

// gcc -lpthread main.c
int main(int argc, char const *argv[])
{
    // sem_init initializes the semaphore
    // sem_init(sem_t *sem, int pshared, unsigned int value);
    // Parameters:
    // 1º - sem_t *sem -> The semaphore
    // 2º - int pshared -> 0 if the semaphore is to be shared between the threads of a process, non-zero otherwise
    // 3º - unsigned int value -> The initial value of the semaphore
    // Return value: 0 if successful, otherwise -1
    sem_init(&sem, 0, 1);

    n = atoi(argv[1]);
    printf("n = %d\n", n);

    Gv = 2 * n;
    printf("Gv = %d\n", Gv);

    // Create two threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread, NULL);
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread, NULL);

    // Wait for the threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Gv = %d\n", Gv);

    // sem_destroy destroys the semaphore
    // sem_destroy(sem_t *sem);
    // Parameters:
    // 1º - sem_t *sem -> The semaphore
    // Return value: 0 if successful, otherwise -1
    sem_destroy(&sem);

    return 0;
}
