/* 
 * comparator.h - Compararing function library
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

/**
 * Define a callback comparator
 */
typedef int (*comparator)(const void *x1, const void *x2);

/**
 * cmp_int - A comparator for integers
 *
 * @x1: *x1 is an integer
 * @x2: *x2 is an integer
 *
 * If *x1 < *x2, return -1.
 * If *x1 = *x2, return  0.
 * If *x1 > *x2, return  1.
 */
extern int cmp_int(const void *x1, const void *x2);

/**
 * cmp_char - A comparator for ASIIC characters
 *
 * @x1: *x1 is an asiic char
 * @x2: *x2 is an asiic char
 *
 * Comparing two elements according to their ASIIC number.
 * If *x1 < *x2, return -1.
 * If *x1 = *x2, return  0.
 * If *x1 > *x2, return  1.
 */
extern int cmp_char(const void *x1, const void *x2);

/**
 * cmp_char - A comparator for pointers
 *
 * @x1: *x1 is a pointer
 * @x2: *x2 is a pointer
 *
 * Comparing two elements according to their memory address.
 * If *x1 < *x2, return -1.
 * If *x1 = *x2, return  0.
 * If *x1 > *x2, return  1.
 */
extern int cmp_pointer(const void *x1, const void *x2);
