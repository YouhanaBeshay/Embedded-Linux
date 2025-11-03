#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <string.h>

int main(int argc, char const *argv[])
{

    char char_input[2];
    int fd = open("/sys/class/leds/input7::capslock/brightness", O_RDWR);
    if (*argv[1] == '1' || *argv[1] == '0')
    {
        write(fd, argv[1], strlen(argv[1]));
        read(fd, char_input, sizeof(char_input));
    }
    close(fd);
    return 0;
}
