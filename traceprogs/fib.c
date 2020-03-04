#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int main(int argc, char ** argv) {
    int i, n, t1 = 0, t2 = 1, nextTerm;
    double start1, finish1;

    if (argc < 2) {
        n = random();
    } else {
        n = strtol(argv[1], NULL, 10);
    }

    printf("Fibonacci Series:\n");

    GET_TIME(start1);
    for (i = 1; i <= n; ++i) {
        printf("%d, ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    GET_TIME(finish1);
    printf("Elapsed time for fib = %e seconds\n",
         finish1-start1);

    return 0;
}