#ifndef BULLET_DARRAY_H
#define BULLET_DARRAY_H

#include <stdio.h>
#include <search.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/*
 * User defines int as DAElemType.
 * DAElemType: dynamic array elements' type.
 */
typedef int DAElemType;

extern DAElemType *save(DAElemType *array, size_t *size, DAElemType val);

#endif /* BULLET_DARRAY_H */
