int main(int argc, char const *argv[])
{
    // Main functions studied

    // mmap
    // mmap maps a file to memory, or in simpler terms,
    // it loads a file to memory, so you can access it like an array
    // Header: sys/mman.h (mman stands for memory management)
    // void *mmap(void * addr, size_t length, int prot, int flags, int fd, off_t offset);
    // Parameters:
    // 1º - void *addr -> The address where the mapping should start. If it is NULL, the kernel
    // 2º - size_t length -> The length of the mapping
    // 3º - int prot -> The protection of the mapping. It can be: PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE
    // 4º - int flags -> The flags of the mapping. It can be: MAP_SHARED, MAP_PRIVATE, MAP_FIXED
    // 5º - int fd -> The file descriptor of the file to be mapped
    // 6º - off_t offset -> The offset in the file where the mapping should start
    // Returns: The address of the mapping

    // mprotect
    // mprotect changes the protection of a memory region
    // Header: sys/mman.h
    // int mprotect(void *addr, size_t len, int prot);
    // Parameters:
    // 1º - void *addr -> The address of the memory region to be changed
    // 2º - size_t len -> The length of the memory region to be changed
    // 3º - int prot -> The new protection of the memory region
    // Returns: 0 on success, -1 on error

    // shmget
    // shmget creates a shared memory segment,
    // shared means that it can be accessed by multiple processes
    // Header: sys/shm.h (shm stands for shared memory)
    // int shmget(key_t key, size_t size, int shmflg);
    // Parameters:
    // 1º - key_t key -> The key of the shared memory segment
    // 2º - size_t size -> The size of the shared memory segment
    // 3º - int shmflg -> The flags of the shared memory segment, it can be: SHM_RDONLY, SHM_RND
    // Returns: The id of the shared memory segment

    // shmat
    // shmat attaches a shared memory segment to the process that called the function
    // Header: sys/shm.h
    // void *shmat(int shmid, const void *shmaddr, int shmflg);
    // Parameters:
    // 1º - int shmid -> The id of the shared memory segment
    // 2º - const void *shmaddr -> The address where the shared memory segment should be attached
    // 3º - int shmflg -> The flags of the shared memory segment, it can be: SHM_RDONLY, SHM_RND
    // Returns: The address of the shared memory segment

    // shmdt
    // shmdt detaches a shared memory segment from the process that called the function
    // Header: sys/shm.h
    // int shmdt(const void *shmaddr);
    // Parameters:
    // 1º - const void *shmaddr -> The address of the shared memory segment to be detached
    // Returns: 0 on success, -1 on error

    // shmctl
    // shmctl controls a shared memory segment
    // Header: sys/shm.h
    // int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    // Parameters:
    // 1º - int shmid -> The id of the shared memory segment
    // 2º - int cmd -> The command to be executed, it can be: IPC_STAT, IPC_SET, IPC_RMID
    // 3º - struct shmid_ds *buf -> A pointer to a struct shmid_ds, it is used to store information about the shared memory segment
    // Returns: 0 on success, -1 on error

    // pthread_create
    // pthread_create creates a new thread
    // Header: pthread.h (pthread stands for POSIX threads)
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    // Parameters:
    // 1º - pthread_t *thread -> A pointer to a pthread_t, it is used to store the id of the thread
    // 2º - const pthread_attr_t *attr -> A pointer to a pthread_attr_t, it is used to store the attributes of the thread
    // 3º - void *(*start_routine) (void *) -> A pointer to a function, it is the function that the thread will execute
    // 4º - void *arg -> A pointer to a void, it is used to pass arguments to the function
    // Returns: 0 on success, -1 on error

    // pthread_join
    // pthread_join waits for a thread to finish
    // Header: pthread.h
    // int pthread_join(pthread_t thread, void **retval);
    // Parameters:
    // 1º - pthread_t thread -> The id of the thread to be waited
    // 2º - void **retval -> A pointer to a void, it is used to store the return value of the thread
    // Returns: 0 on success, -1 on error

    // sem_init
    // sem_init initializes a semaphore
    // Header: semaphore.h
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    // Parameters:
    // 1º - sem_t *sem -> A pointer to a sem_t, it is used to store the semaphore
    // 2º - int pshared -> If it is 0, the semaphore is shared between threads, if it is 1, the semaphore is shared between processes
    // 3º - unsigned int value -> The initial value of the semaphore
    // Returns: 0 on success, -1 on error

    // sem_wait
    // sem_wait waits for a semaphore to be available
    // Header: semaphore.h
    // int sem_wait(sem_t *sem);
    // Parameters:
    // 1º - sem_t *sem -> A pointer to a sem_t, it is used to store the semaphore
    // Returns: 0 on success, -1 on error

    // sem_timedwait
    // sem_timedwait waits for a semaphore to be available, but it has a timeout
    // Header: semaphore.h
    // int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    // Parameters:
    // 1º - sem_t *sem -> A pointer to a sem_t, it is used to store the semaphore
    // 2º - const struct timespec *abs_timeout -> A pointer to a struct timespec, it is used to store the timeout
    // Returns: 0 on success, -1 on error

    // sem_post
    // sem_post increases the value of a semaphore
    // Header: semaphore.h
    // int sem_post(sem_t *sem);
    // Parameters:
    // 1º - sem_t *sem -> A pointer to a sem_t, it is used to store the semaphore
    // Returns: 0 on success, -1 on error

    return 0;
}
