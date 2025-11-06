
#include <stdint.h>
#include <string.h>
void myprint(char *buffer, uint64_t size)
{
    asm("mov $1 ,%%rax\n\t" 
        "mov $1 ,%%rdi\n\t" // write on file descriptor "1"
        "mov %0 ,%%rsi\n\t"
        "mov %1 ,%%rdx\n\t"
        "syscall"
        :
        : "r"(buffer), "r"(size)
        : "%rax", "%rdi", "%rsi", "%rdx");
}
int main(int argc, char const *argv[])
{
    char test_string[] = "This line was printed using assembly and syscalls !\n";
    myprint(test_string, strlen(test_string));
    return 0;
}
