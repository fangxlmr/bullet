/*
 * comparator
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
