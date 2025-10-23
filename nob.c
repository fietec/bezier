#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    cmd_append(&cmd, "gcc");
    cmd_append(&cmd, "-o", "bezier");
    cmd_append(&cmd, "bezier.c");
    cmd_append(&cmd, "-lraylib", "-lGL", "-lm", "-lpthread" ,"-ldl" ,"-lrt" ,"-lX11");

    if (!cmd_run(&cmd)) return 1;
    return 0;
}
