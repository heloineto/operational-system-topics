/*-------------------------------------------------------------------------

PROBLEMA

Um servidor é dividido em 6 threads posix; há 7 conexões de rede, e cada
thread faz movimentação de dados entre 2 conexões, conforme o esquema
a seguir:

T0 c0 c1
T1 c1 c2
T2 c2 c3
T3 c3 c4
T4 c4 c5
T5 c5 c6

Cada thread gasta um tempo aleatório entre os valores t1 e t2,
durante o qual usa suas duas conexões. Depois disso, cada thread gasta
um tempo aleatório (também entre t1 e t2) gerando um relatório em disco.

Escreva código para representar/simular esse problema,
utilizando primitivas de sincronia.

Você deve escrever duas versões de solução:

(A) apenas uma thread está trabalhando; e
(B) mais de uma thread pode estar trabalhando - desde que, lógico,
    possa tomar posse de suas duas conexões.

------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdarg.h>

#define NUM_THREADS 6
#define NUM_CONNECTIONS 7

// Colors to diferenciante threads
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

char *colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
int *connections;
sem_t semaphores[NUM_CONNECTIONS];

void *thread();
void *get_args(int index);
void init_connections();
void init_semaphores();
void use_connection(int index);
void clean_up();

// Warning: You need to use -lpthread option to compile this program.
int main(int argc, char const *argv[])
{
    init_connections();
    init_semaphores();

    pthread_t *threads = (pthread_t *)malloc(NUM_THREADS * sizeof(pthread_t));

    for (int i = 0; i < NUM_THREADS; i++)
    {
        void *args = get_args(i);
        pthread_create(&threads[i], NULL, thread, args);
    }

    // You have to wait for all threads to finish before exiting the program.
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONNECTIONS; i++)
    {
        printf("c%d = %d\n", i, connections[i]);
    }

    free(threads);
    clean_up();

    return 0;
}

void *thread(void *args)
{
    int id = ((int *)args)[0];
    int connection_time = 100;
    int report_time = 50;

    // printf("%s", colors[id]);
    log(id, "[THREAD %d] started\n", id);
    log(id, "[THREAD %d] connecting to c%d = %d; and c%d = %d;\n", id, id, connections[id], id + 1, connections[id + 1]);

    use_connection(id);
    use_connection(id + 1);

    sleep(connection_time / 1000);

    log(id, "[THREAD %d] disconnecting to c%d = %d; and c%d = %d; (%dms)\n", id, id, connections[id], id + 1, connections[id + 1], connection_time);
    log(id, "[THREAD %d] generating report (%dms)\n", id, report_time);
    sleep(report_time / 1000);

    log(id, "[THREAD %d] ended\n", id);
    // printf("%s", RESET);
}

void *get_args(int index)
{
    void *args = (void *)malloc(sizeof(int));
    ((int *)args)[0] = index;
    return args;
}

void init_connections()
{
    connections = (int *)malloc(NUM_CONNECTIONS * sizeof(int));
    for (int i = 0; i < NUM_CONNECTIONS; i++)
    {
        connections[i] = 0;
    }
}

void init_semaphores()
{
    for (int i = 0; i < NUM_CONNECTIONS; i++)
    {
        sem_init(&semaphores[i], 0, 1);
    }
}

void use_connection(int index)
{
    sem_wait(&semaphores[index]);
    // This makes it so 0 -> 1 and 1 -> 0
    connections[index] = 1 - connections[index];
    sem_post(&semaphores[index]);
}

void clean_up()
{
    free(connections);
    for (int i = 0; i < NUM_CONNECTIONS; i++)
    {
        sem_destroy(&semaphores[i]);
    }
}

void log(int id, const char *format, ...)
{
    printf("%s", colors[id]);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("%s", RESET);
}