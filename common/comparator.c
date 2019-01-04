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

#include <stdint.h>
#include "comparator.h"

int cmp_int(const void *x1, const void *x2)
{
    return *(int *) x1 - *(int *) x2;
}

int cmp_char(const void *x1, const void *x2)
{
    return *(char *) x1 - *(char *) x2;
}

int cmp_pointer(const void *x1, const void *x2)
{
    return *(uintptr_t *) x1 - *(uintptr_t *) x2;
}
