/* 
 * comparator.c
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
