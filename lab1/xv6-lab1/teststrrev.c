#include "types.h"
#include "stat.h"
#include "user.h"
int main(void) {
char buf[32] = "Keshav Mishra"; //this string will be passed to our newly created system call
printf(1,"Before: %s\n", buf);
strrev(buf, strlen(buf)); //passing string and string length
printf(1, "After: %s\n", buf);
exit();
}