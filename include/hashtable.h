/*
 * hashtable.h
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
   All rights reserved.
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

#ifndef BULLET_HASHTABLE_H
#define BULLET_HASHTABLE_H

typedef struct _hashtable hashtable_t;

extern hashtable_t *hashtable_new(void);

extern void hashtable_free(hashtable_t *ht);

extern int hashtable_set(hashtable_t *ht,
        size_t key_size, const void *key,
        size_t value_size, const void *value);

extern int hashtale_get(hashtable_t *ht, )

#endif /* BULLET_HASHTABLE_H */
