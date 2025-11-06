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

    char string_process2[SIZE] = {0};
    strcpy(string_process2, ptr);

    printf("Process 2 read '%s' from the shared memory\n", string_process2);

    shmdt(ptr);
}