#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// This program is used to read the shared memory segment created by "./mem-segment-2.c"
// It is used to show that the shared memory segment is not in the heap, but in the data segment, because if it was in the heap,
// it would be destroyed when the process that created it ended. However, it is not destroyed, because the data segment is not volatile.
// Use this in conjunction with "./mem-segment-1.c"
int main(int argc, char const *argv[])
{

    key_t key = 666;

    // The shmget function is used to create a shared memory segment
    // Header: #include <sys/ipc.h>
    // Prototype: int shmget(key_t key, size_t size, int shmflg);
    // Parameters:
    // 1º - key_t key -> The key of the shared memory segment
    // 2º - size_t size -> The size of the shared memory segment
    // 3º - int shmflg -> The flags of the shared memory segment
    // Returns: int -> The id of the shared memory segment
    int id = shmget(key, 1000000, IPC_CREAT | 0666);

    // The shmat function is used to attach a shared memory segment to the address space of the calling process
    // Header: #include <sys/shm.h>
    // Prototype: void *shmat(int shmid, const void *shmaddr, int shmflg);
    // Parameters:
    // 1º - int shmid -> The id of the shared memory segment
    // 2º - const void *shmaddr -> The address where the shared memory segment will be attached
    // 3º - int shmflg -> The flags of the shared memory segment
    // Returns: void * -> The address where the shared memory segment was attached
    char *p = shmat(id, NULL, 0);

    while (p != (char *)0xFFFFFFFF)
    {
        printf("%c\n", *p);
    }

    // The shmcntl function is used to control a shared memory segment
    // Header: #include <sys/shm.h>
    // Prototype: int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    // Parameters:
    // 1º - int shmid -> The id of the shared memory segment
    // 2º - int cmd -> The command to be executed
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
