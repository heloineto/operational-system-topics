/**
 * O Algoritmo de Peterson é um algoritmo clássico usado para garantir a
 * exclusão mútua em sistemas concorrentes. No entanto, existem certas
 * condições em que o algoritmo pode falhar.
 *
 * Ele funciona corretamente quando ambas as seguintes condições são satisfeitas:
 *
 * - Execução justa: O algoritmo presume que os processos compartilhados competem
 *   de forma justa pela seção crítica. Isso significa que, se um processo deseja
 *   entrar na seção crítica, eventualmente ele será capaz de fazê-lo, a menos que
 *   seja impedido por outro processo. Se a execução não for justa, o algoritmo
 *   pode não funcionar corretamente.
 *
 * - Instrução de troca atômica: O algoritmo assume que existe uma instrução de
 *   troca atômica, que permite que duas variáveis sejam lidas e escritas de forma
 *   atômica, sem a interferência de outros processos. Essa operação atômica é
 *   essencial para o funcionamento correto do algoritmo. Se a instrução de troca
 *   atômica não estiver disponível no sistema, o algoritmo pode não funcionar
 *   corretamente.
 *
 * Além dessas condições, o algoritmo também pode apresentar problemas de
 * desempenho e possíveis condições de corrida, dependendo da implementação
 * específica e das características do sistema em que é aplicado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int flag[2] = {0, 0};
int turn = 0;

// Algoritmo de Peterson (https://pt.wikipedia.org/wiki/Algoritmo_de_Peterson)
void *thread1(void *args)
{
    flag[0] = 1;
    turn = 1;
    while (flag[1] == 1 && turn == 1)
    {
        // ocupado, espere
    }
    printf("[thread1] parte crítica\n");
    sleep(1);
    printf("[thread1] fim da parte crítica\n");
    flag[0] = 0;
}

void *thread2(void *args)
{
    flag[1] = 1;
    turn = 0;
    while (flag[0] == 1 && turn == 0)
    {
        // ocupado, espere
    }
    printf("[thread2] parte crítica\n");
    sleep(1);
    printf("[thread2] fim da parte crítica\n");
    flag[1] = 0;
}

int main(int argc, char const *argv[])
{

    // Create two threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread2, NULL);

    // Wait for the threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
