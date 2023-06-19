#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n = 0;

void *thread(void *s)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", (char *)s);
    }
}

// This program is to show that threads are executed concurrently. The output of this program is not deterministic. (It may be different every time you run it.)
// Warning: You need to use -lpthread option to compile this program. Because pthread is not a part of C11 standard.
// gcc -lpthread main.c
int main(int argc, char const *argv[])
{
    n = atoi(argv[1]);

    printf("n = %d\n", n);

    // Create two threads

    // pthread_t is a type that represents a thread
    pthread_t tid1;

    // pthread_create is a function that creates a thread
    // Header: #include <pthread.h>
    // Prototype: int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    // Parameters:
    // 1º - pthread_t *thread -> A pointer to the thread
    // 2º - const pthread_attr_t *attr -> The attributes of the thread
    // 3º - void *(*start_routine) (void *) -> The function that will be executed by the thread
    // 4º - void *arg -> The arguments of the function that will be executed by the thread
    // Returns: int -> 0 if the thread was created successfully, otherwise it returns an error code
    pthread_create(&tid1, NULL, thread, (void *)"()");
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread, (void *)"{}");

    // Wait for the threads to finish

    // pthread_join is a function that waits for a thread to finish
    // Header: #include <pthread.h>
    // Prototype: int pthread_join(pthread_t thread, void **retval);
    // Parameters:
    // 1º - pthread_t thread -> The thread that will be waited
    // 2º - void **retval -> The return value of the thread
    // Returns: int -> 0 if the thread was waited successfully, otherwise it returns an error code
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
