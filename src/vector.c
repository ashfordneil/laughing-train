#include "vector.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

enum Error vector_create(struct Vector* parameter, void (*destroy)(void*)) {
    struct Vector output;

    output.destroy = destroy;
    output.size = 0;
    output.capacity = INITIAL_SIZE;
    output.data = malloc(sizeof(void*) * output.capacity);

    if (output.data == NULL) {
        return MALLOC_ERROR;
    }

    memmove(parameter, &output, sizeof(struct Vector));

    return OKAY;
}

void vector_delete(struct Vector* parameter) {
    if (parameter->destroy) {
        for (int i = 0; i < parameter->size; ++i) {
            parameter->destroy(parameter->data[i]);
        }
    }

    free(parameter->data);
}

enum Error vector_push(struct Vector* parameter, void* element) {
    if (parameter->size == parameter->capacity) {
        // create a temporary vector for resizing so that updates to the data
        // structure can be avoided until after all error-prone sections of code
        // are complete.
        struct Vector temp = *parameter;
        temp.capacity *= 2;
        temp.data = realloc(temp.data, sizeof(void*) * temp.capacity);

        if (temp.data == NULL) {
            return MALLOC_ERROR;
        }

        memmove(parameter, &temp, sizeof(struct Vector));
    }

    parameter->data[parameter->size++] = element;

    return OKAY;
}
