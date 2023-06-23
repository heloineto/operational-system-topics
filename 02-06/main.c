#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int child(char *var, int index);

// Gmag is an array of chars
char Gmag[10] = "Oi";
// Gp is a pointer to a string literal
char *Gp = "Olá";
// This is how they are different in practice:
// Gmag is an array of chars, so it is allocated in the stack, while
// Gp is a pointer to a string literal, so it is allocated in the data segment

// This function creates 3 children (from the same parent)
// And passes a pointer of characters to it
// 1º child -> is able to read and write `Gmag`
// 2º child -> is able to read `Gp`, but not write it. (because it is in a data segment)
// 3º child -> is able to read the address of main, but if we try to write to it (as we do)
// the program is killed immediately by the kernel. No warnings, no error messages, just cold, instantaneous death.
int main(int argc, char const *argv[])
{
    char *p = (char *)main;

    int is_child = fork();

    if (is_child)
    {
        child(Gmag, 1);
        return 0;
    }

    is_child = fork();

    if (is_child)
    {
        child(Gp, 2);
        return 0;
    }

    is_child = fork();

    if (is_child)
    {
        child(p, 3);
        return 0;
    }

    printf("\n");

    return 0;
}

int child(char *var, int index)
{
    printf("[CHILD %d] address = %p, value = \"%s\"\n", index, var, var);

    *(var + 0) = 'X'; // same as var[0] = 'X'; or var* = 'X'

    printf("[CHILD %d] address = %p, value = \"%s\"\n", index, var, var);

    printf("[CHILD %d] Pronto terminou\n", index);
    return 0;
}