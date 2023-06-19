
#include <stdio.h>

// Gmag is an array of chars
char Gmag[10] = "Oi";
// Gp is a pointer to a string literal
char *Gp = "Olá";
// This is how they are different in practice:
// Gmag is an array of chars, so it is allocated in the stack, while
// Gp is a pointer to a string literal, so it is allocated in the data segment

void printFile(FILE *file);

int main(int argc, char const *argv[])
{
    char *p = (char *)main;

    // This is a file that contains the memory map of the process
    FILE *file = fopen("/proc/self/maps", "rt");

    printFile(file);

    // Explanations:
    // You can use this file to see where the variables are allocated, and what
    // permissions they have:
    // r -> read
    // w -> write
    // x -> execute
    // s -> shared
    // p -> private

    return 0;
}

// Prints the contents of a file
void printFile(FILE *file)
{
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        putchar(c);
    }
}