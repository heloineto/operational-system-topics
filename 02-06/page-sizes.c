#include <stdio.h>
#include <unistd.h>

// This function uses the sysconf function to get the page size
// A page in c normally has 4096 bytes
int main(int argc, char const *argv[])
{
    // The sysconf function is from the unistd.h header
    // Description: This function is used to get system variables (like the page size)
    // long sysconf(int);
    // Parameters:
    // 1º - int name -> The name of the system variable to be retrieved
    int pageSize = sysconf(_SC_PAGESIZE);

    char *p1 = "X";

    char *pageAddress = (char *)(((unsigned long)p1) & ~(pageSize - 1));

    printf("pageAddress = %p\n", pageAddress);

    return 0;
}
