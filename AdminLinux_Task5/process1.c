#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>

#include <string.h>
#include <stdio.h>

#define SHARED_KEY 1234567
#define SIZE 100

int main(int argc, char const *argv[])
{
    // Added  " | 0600" to give the user read and write permisions
    int key = shmget(SHARED_KEY, SIZE, IPC_CREAT | 0600);
    char *ptr = shmat(key, NULL, 0);

    if (argv[1] == NULL)
    {
        printf(" No input given");
        return 1;
    }
    else if (strlen(argv[1]) > SIZE)
    {
        printf(" input size is bigger than allocated shared memory");
        return 1;
    }
    else
    {
        strcpy(ptr, argv[1]);

        printf("Process 1 wrote '%s' in the shared memory\n", argv[1]);
    }
    shmdt(ptr);

    return 1;
}