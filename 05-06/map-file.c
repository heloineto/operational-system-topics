
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void printMemoryMaps();

int main(int argc, char const *argv[])
{
    // The open function is from the fcntl.h header
    // int open(const char *, int, ...);
    // Parameters:
    // 1º - const char *pathname -> The path to the file to be opened
    // 2º - int flags -> The flags of the file to be opened. It can be: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL, O_TRUNC, O_APPEND
    // 3º - ... -> The permissions of the file to be opened. It is only used if O_CREAT is passed in the flags parameter
    int fd = open("text.txt", O_RDONLY);

    struct stat textStat;

    // The fstat function is from the sys/stat.h header
    // int fstat(int, struct stat *);
    // Parameters:
    // 1º - int fd -> The file descriptor of the file to be mapped
    // 2º - struct stat *buf -> A pointer to a struct stat, where the information about the file will be stored
    fstat(fd, &textStat);

    // The mmap function is from the sys/mman.h header
    // Description: This function maps a file to memory, it's different from reading the file using the read function, because the file is mapped to memory, so you can access it like an array, while the read function reads the file byte by byte. This function is used to read files that are too big to be read using the read function.
    // void  *mmap(void *, size_t, int, int, int, off_t);
    // Parameters:
    // 1º - void *addr -> The address where the mapping should start. If it is NULL, the kernel
    // 2º - size_t length -> The length of the mapping
    // 3º - int prot -> The protection of the mapping. It can be: PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE
    // 4º - int flags -> The flags of the mapping. It can be: MAP_SHARED, MAP_PRIVATE, MAP_FIXED
    // 5º - int fd -> The file descriptor of the file to be mapped
    // 6º - off_t offset -> The offset in the file where the mapping should start
    char *ptr = mmap(NULL, textStat.st_size, PROT_READ, MAP_SHARED, fd, 0);

    // This prints the contents of the file
    for (int i = 0; i < textStat.st_size; i++)
    {
        putchar(*(ptr + i));
    }
    putchar('\n');

    return 0;
}