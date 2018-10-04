#include "comparator.h"

int cmp_int(const void *x1, const void *x2)
{
    int *y1, *y2;

    y1 = (int *) x1;
    y2 = (int *) x2;

    if (y1 < y2) {
        return -1;
    } else if (y1 == y2) {
        return 0;
    } else {
        return 1;
    }
}

int cmp_char(const void *x1, const void *x2)
{
    char *c1, *c2;

    c1 = (char *) x1;
    c2 = (char *) x2;

    if (c1 < c2) {
        return -1;
    } else if (c1 == c2) {
        return 0;
    } else {
        return 1;
    }
}

int cmp_pointer(const void *x1, const void *x2)
{
    unsigned int *p1, *p2;

    p1 = (unsigned int *) x1;
    p2 = (unsigned int *) x2;

    if (p1 < p2) {
        return -1;
    } else if (p1 == p2) {
        return 0;
    } else {
        return 1;
    }
}
