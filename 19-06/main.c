#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <signal.h>
#include <string.h>

sem_t sem;
struct timespec wait_time;
int seconds;

int sem_timedwait_relative(sem_t *sem, int seconds);
void print_errno();

void *thread()
{

    // sem_timedwait waits for a semaphore to be available,
    // but only for a specified amount of time
    // Prototype: int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    // Parameters:
    // 1º - sem: A pointer to the semaphore to wait on
    // 2º - abs_timeout: A pointer to a timespec structure that specifies an absolute timeout in seconds and nanoseconds
    // Returns:
    // 0 if the semaphore was successfully decremented (signaling success to the caller)
    // -1 if an error occurred (errno is set to indicate the error)
    int wait_return = sem_timedwait_relative(&sem, seconds);

    printf("wait_return = %d\n", wait_return);
    printf("errno = %d\n", errno);

    switch (wait_return)
    {
    case 0:
        printf("The semaphore was successfully decremented\n");
        break;
    default:
        printf("An error occurred\n");
        // strerror() returns a pointer to a string that describes
        // the error code passed in the argument errnum.
        // I won't use it because it is too generic.
        // printf("Error: %s\n", strerror(errno));
        print_errno();

        return NULL;
        break;
    }

    printf("Critical section\n");
    sleep(5);

    sem_post(&sem);
}

// gcc main.c -lpthread
int main(int argc, char const *argv[])
{
    seconds = atoi(argv[1]);
    sem_init(&sem, 0, 1);

    // Create two threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread, NULL);
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread, NULL);

    // Wait for the threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&sem);

    return 0;
}

int sem_timedwait_relative(sem_t *sem, int seconds)
{
    if (clock_gettime(CLOCK_REALTIME, &wait_time) == -1)
    {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    wait_time.tv_sec += seconds;

    int wait_return = sem_timedwait(sem, &wait_time);
}

void print_errno()
{
    // Source: (https://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_timedwait.html)
    // The sem_timedwait() function shall fail if:
    // [EINVAL] The process or thread would have blocked, and the abstime parameter specified a nanoseconds field value less than zero or greater than or equal to 1000 million.
    // [ETIMEDOUT] The semaphore could not be locked before the specified timeout expired.
    //
    // The sem_timedwait() function may fail if:
    // [EDEADLK] A deadlock condition was detected.
    // [EINTR] A signal interrupted this function.
    // [EINVAL] The sem argument does not refer to a valid semaphore.

    switch (errno)
    {
    case EINVAL:
        printf("The process or thread would have blocked, and the abstime parameter specified a nanoseconds field value less than zero or greater than or equal to 1000 million.\n");
        break;
    case ETIMEDOUT:
        printf("The semaphore could not be locked before the specified timeout expired.\n");
        break;
    case EDEADLK:
        printf("A deadlock condition was detected.\n");
        break;
    case EINTR:
        printf("A signal interrupted this function.\n");
        break;
    case EAGAIN:
        printf("The semaphore could not be locked.\n");
        break;

    default:
        break;
    }
}