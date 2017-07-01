#include "vector.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

enum Error vector_copy(struct Vector* self, const struct Vector* input)
{
    struct Vector output;

    output.destroy = input->destroy;
    output.element_size = input->element_size;
    output.capacity = input->capacity;
    output.size = input->size;
    output.data = malloc(output.element_size * output.capacity);

    if (output.data == NULL) {
        return MALLOC_ERROR;
    }

    memcpy(output.data, input->data, output.size * output.element_size);

    memcpy(self, &output, sizeof(struct Vector));

    return OKAY;
}

enum Error vector_create(
        struct Vector* self, size_t element_size, void (*destroy)(void*))
{
    struct Vector output;

    output.destroy = destroy;
    output.element_size = element_size;
    output.capacity = INITIAL_CAPACITY;
    output.size = 0;
    output.data = malloc(output.element_size * output.capacity);

    if (output.data == NULL) {
        return MALLOC_ERROR;
    }

    memcpy(self, &output, sizeof(struct Vector));

    return OKAY;
}

void vector_delete(struct Vector* self)
{
    if (self->destroy) {
        for (int i = 0; i < self->size; ++i) {
            self->destroy(self->data + self->element_size * i);
        }
    }

    free(self->data);
}

enum Error vector_push(struct Vector* self, const void* element)
{
    if (self->size == self->capacity) {
        // create a temporary vector for resizing so that updates to the data
        // structure can be avoided until after all error-prone sections of
        // code are complete.
        struct Vector temp = *self;
        temp.capacity *= 2;
        temp.data = realloc(temp.data, temp.element_size * temp.capacity);

        if (temp.data == NULL) {
            return MALLOC_ERROR;
        }

        *self = temp;
    }

    // copy element into the vector
    memcpy(self->data + self->element_size * self->size, element,
            self->element_size);

    self->size += 1;

    return OKAY;
}

enum Error vector_pop(struct Vector* self, void* value)
{
    if (self->size == 0) {
        return RANGE_ERROR;
    }

    self->size -= 1;

    const void* output = self->data + (self->element_size * self->size);

    if (value != NULL) {
        memcpy(value, output, self->element_size);
    }

    return OKAY;
}

enum Error vector_insert(
        struct Vector* self, size_t index, const void* element)
{
    if (self->size < index) {
        return RANGE_ERROR;
    }

    if (self->size == self->capacity) {
        struct Vector temp = *self;
        temp.capacity *= 2;
        temp.data = realloc(temp.data, temp.element_size * temp.capacity);

        if (temp.data == NULL) {
            return MALLOC_ERROR;
        }

        *self = temp;
    }

    memmove(self->data + (index + 1) * self->element_size,
            self->data + index * self->element_size,
            self->element_size * (self->size - index - 1));

    memcpy(self->data + index * self->element_size, element,
            self->element_size);

    self->size += 1;

    return OKAY;
}

enum Error vector_remove(struct Vector* self, size_t index, void* value)
{
    if (self->size <= index) {
        return RANGE_ERROR;
    }

    if (value != NULL) {
        memcpy(value, self->data + (self->element_size * index),
                self->element_size);
    }

    memmove(self->data + self->element_size * index,
            self->data + self->element_size * (index + 1),
            self->element_size * (self->size - index - 1));

    self->size -= 1;

    return OKAY;
}

enum Error vector_swap_remove(struct Vector* self, size_t index, void* value)
{
    if (self->size <= index) {
        return RANGE_ERROR;
    }

    if (value != NULL) {
        memcpy(value, self->data + self->element_size * index,
                self->element_size);
    }

    memcpy(self->data + self->element_size * index,
            self->data + self->element_size * (self->size - 1),
            self->element_size);

    self->size -= 1;

    return OKAY;
}