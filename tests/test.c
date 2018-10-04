#include <stdio.h>
#include "maxheap.h"

int compare(void *key1, void *key2)
{
    return *(int *)key1 - *(int *)key2;
}

int main (void) {
    int a[] = {233333333, 9, 39, 28323, 999, -5, 23, 45, 1, -2, 555, 2222222};
    int b = 233333334;
    int c = 20;
    printf("hello, world.\n");

    MaxHeap *maxheap;

    maxheap = maxheap_new(20, compare);
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
        maxheap_add(maxheap, a + i);
    }
    printf("max = %d\n", *(int *) maxheap_get_root(maxheap));
    printf("max heap %d full.\n", maxheap_is_full(maxheap));
    printf("depth of maxheap = %d\n", maxheap_depth(maxheap));
    maxheap_add(maxheap, &b);
    printf("max = %d\n", *(int *) maxheap_get_root(maxheap));
    maxheap_pop_root(maxheap);
    printf("max = %d\n", *(int *) maxheap_get_root(maxheap));
    maxheap_find(maxheap, a + 0);
    printf("a + 0 is %d in maxheap.\n", maxheap_find(maxheap, a + 0));
    maxheap_del(maxheap, a + 0);
    printf("a + 0 is %d in maxheap.\n", maxheap_find(maxheap, a + 0));
    printf("c is %d in maxheap.\n", maxheap_find(maxheap, &c));
    printf("Done.\n");
    return 0;
}
