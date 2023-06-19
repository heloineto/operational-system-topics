
#include <stdio.h>
#include <stdlib.h>

void printMemoryMaps();

// This program allocates 1000000 bytes of memory, and prints the memory map
// before and after the allocation. The expected place for the allocation is the heap
// However, if the size of the allocation is too big, the allocation will be done in the
// data segment, because the heap is not big enough. Usually, the heap is 8MB, but it can
// be changed with the command ulimit -v <size in KB>
int main(int argc, char const *argv[])
{
    printf("BEFORE ALLOCATION:\n\n");
    printMemoryMaps();

    int *ptr = malloc(1000000);

    printf("\nAFTER ALLOCATION:\n\n");
    printMemoryMaps();

    printf("\nptr_start = %p; ptr_end = %p\n", ptr, ptr + 999999);

    *(ptr + 99999) = 1;

    return 0;
}

// See memory-map.c for an explanation of this function (02-06/memory-map.c)
void printMemoryMaps()
{
    FILE *file = fopen("/proc/self/maps", "rt");

    for (int c; (c = fgetc(file)) != EOF;)
    {
        putchar(c);
    }
}