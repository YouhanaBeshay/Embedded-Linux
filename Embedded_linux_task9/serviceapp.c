#include <stdio.h>
#include <unistd.h>

int main(void)
{
    while (1)
    {
    printf("Hello ITI - From a Systemd Service \n");
    // flush the stdout buffer
    // fflush(stdout);

    sleep(1);
    }
    


    return 0;
}