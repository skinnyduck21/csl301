#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    setflag(1140);
    printf(1, "Flag after set to 1140: %d\n", getflag());

    setflag(4321);
    printf(1, "Flag after set to 4321: %d\n", getflag());

    exit();
}
