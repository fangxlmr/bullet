/*
 * Min heap
 */
#include <stdio.h>

void shiftdown(int *h, int n, int i);
void shifup(int *h, int n, int i);
static void swap(int *h, int x, int y);

/* Shift down nodes */
void shiftdown(int *h, int n, int i)
{
    int t, flag;

    flag = 0;

    /* If there is at least one child*/
    while (i * 2 + 1 < n && flag == 0) {
        /* Compare it with left child */
        if (h[i] > h[i * 2 + 1]) {
            t = i * 2 + 1;
        } else {
            t = i;
        }
        /* Compare it with right child if there is any */
        if (i * 2 + 2 < n && h[t] > h[i * 2 + 2]) {
            t = i * 2 + 2;
        }

        /* Swap if needed */
        if (t != i) {
            swap(h, t, i);
            i = t;
        } else {
            flag = 1;
        }
    }
}

/* Shift up nodes */
void shiftup(int *h, int n, int i)
{
    int flag;

    flag = 0;
    if (i == 0 && i >= n) {
        return;
    }
    while (i != 1 && flag == 0) {
        /* Compare it with parent nodes */
        if (h[i] < h[(i - 1) / 2]) {
            swap(h, i, (i - 1) / 2);
        } else {
            flag = 1;
        }

        i = (i - 1) / 2;
    }
}

void swap(int *v, int x, int y)
{
    int temp;

    temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}
