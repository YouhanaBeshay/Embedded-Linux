#include <command.h>
#include <stdio.h>

#ifdef CONFIG_CMD_SAY_MY_NAME
static int do_say_my_name(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    printf("You're Youhana\n");
    return 0;
}

U_BOOT_CMD(
    say_my_name,      /* command name */
    1,          /* max args */
    1,          /* repeatable */
    do_say_my_name,   /* handler function */
    "Says my name",        /* short help */
    ""          /* long help */
);

#endif