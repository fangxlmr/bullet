#include "darray.h"
#define FACTOR 1.5

size_t ARRAY_SIZE = 100;

DAElemType *save(DAElemType *array, size_t *size, const DAElemType val) {
    /*
     * First time to store values
     */
    if (array == NULL) {
        array = (DAElemType *) malloc(ARRAY_SIZE * sizeof(DAElemType));
        *size = 0;
        array[(*size)++] = val;
        return array;
    }

    /*
     * no overflow happens
     */
    if (*size < ARRAY_SIZE) {
        array[(*size)++] = val;
        return array;
    } else {                /* overflow happens */
        DAElemType *tmp = array;
        array = realloc(array, (size_t) (FACTOR * ARRAY_SIZE * sizeof(DAElemType)));
        if (array) {
            memcpy(array, tmp, *size * sizeof(DAElemType));
            free(tmp);
            return array;
        } else {
            printf("Dynamic array is full. \n"
                   "And resize dynamic array failed.\n");
            return array;
        }
    }
}

