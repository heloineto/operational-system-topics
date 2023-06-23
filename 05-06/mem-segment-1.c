#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// This program creates a shared memory segment, and reads from the standard input (keyboard)
// to write to the shared memory segment. The program ends when the user presses CTRL+D.
// Use this in conjunction with "./mem-segment-2.c"
int main(int argc, char const *argv[])
{

    key_t key = 666;

    // Header: #include <sys/ipc.h> (ipc stands for inter-process communication)
    // Prototype: int shmget(key_t key, size_t size, int shmflg);
    // Parameters:
    // 1º - key_t key -> The key of the shared memory segment
    // 2º - size_t size -> The size of the shared memory segment
    // 3º - int shmflg -> The flags of the shared memory segment
    // Returns: int -> The id of the shared memory segment
    int id = shmget(key, 1000000, IPC_CREAT | 0666);

    // The shmat function is used to attach a shared memory segment to the address space of the calling process
    // Header: #include <sys/shm.h> (shm stands for shared memory)
    // Prototype: void *shmat(int shmid, const void *shmaddr, int shmflg);
    // Parameters:
    // 1º - int shmid -> The id of the shared memory segment
    // 2º - const void *shmaddr -> The address where the shared memory segment will be attached
    // 3º - int shmflg -> The flags of the shared memory segment
    // Returns: void * -> The address where the shared memory segment was attached
    char *p = shmat(id, NULL, 0);

    while (p != (char *)0xFFFFFFFF)
    {
        scanf("%c", p);
    }

    // The shmcntl function is used to control a shared memory segment
    // Header: #include <sys/shm.h>
    // Prototype: int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    // Parameters:
    // 1º - int shmid -> The id of the shared memory segment
    // 2º - int cmd -> The command to be executed, it can be:
    //   - IPC_STAT -> Used to get information about the shared memory segment
    //   - IPC_SET -> Used to set information about the shared memory segment
    //   - IPC_RMID -> Used to remove the shared memory segment
    // 3º - struct shmid_ds *buf -> A pointer to a struct shmid_ds
    // Returns: int -> 0 on success; -1 on error
    shmctl(id, IPC_RMID, NULL);

    // The shmdt function is used to detach a shared memory segment from the address space of the calling process
    // Header: #include <sys/shm.h>
    // Prototype: int shmdt(const void *shmaddr);
    // Parameters:
    // 1º - const void *shmaddr -> The address where the shared memory segment is attached
    // Returns: int -> 0 on success; -1 on error
    shmdt(p);

    return 0;
}
