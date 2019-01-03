/*
 * hashtable.c
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

#include <stdlib.h>
#include "hashtable.h"

int hashtable_new(hashtable_t *hashtable, const comparator cmp) {
    return dict_new(hashtable, cmp);
}

void hashtable_free(hashtable_t *hashtable)
{
    dict_free(hashtable);
}

int hashtable_add(hashtable_t hashtable, const hashtableElem x)
{
    return dict_add(hashtable, x, NULL);
}

int hashtable_contains(hashtable_t hashtable, const hashtableElem x)
{
    return dict_contains_key(hashtable, x);
}

int hashtable_remove(hashtable_t hashtable, const hashtableElem x)
{
    return dict_remove(hashtable, x);
}
