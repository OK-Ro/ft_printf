#include <stdio.h>
int main() {
    printf(" %p ", (void *)NULL);
    printf(" %p ", (void *)42);
    printf(" %p %p ", (void *)42, (void *)NULL);
    return 0;
}
