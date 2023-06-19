#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int Gv;
int n;

void *thread(void *s)
{
    for (int i = 0; i < n; i++)
    {
        Gv -= 1;
    }
}

// This program shows that threads share the same memory space.
int main(int argc, char const *argv[])
{
    n = atoi(argv[1]);
    printf("n = %d\n", n);

    Gv = 2 * n;

    printf("Gv = %d\n", Gv);

    // Create two threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread, (void *)"()");
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread, (void *)"{}");

    // Wait for the threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Gv = %d\n", Gv);

    return 0;
}
