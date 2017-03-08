/**
 * @file vector.h
 * @author Neil Ashford
 * @date 5 March 2017
 */

#ifndef _LT_VECTOR_
#define _LT_VECTOR_

#include "error.h"

#include <stddef.h>

/**
 * @brief A contiguous list to store generic data types.
 */
struct Vector {
    /**
     * @brief A helper function to clean up an individual element of the
     * vector. Set this to NULL if no cleanup is necessary.
     *
     * @param element The element being cleaned up.
     */
    void (*destroy)(void* element);
    /// The size of each element in the vector.
    size_t element_size;
    /// The number of elements that fit within the vector.
    size_t capacity;
    /// The number of elements currently stored in the vector.
    size_t size;
    /// The actual data stored in the vector.
    void* data;
};

// copies a vector
enum Error vector_copy(struct Vector* output, const struct Vector* input);

/**
 * @brief Creates a new vector.
 *
 * @param element_size The size of an individual element in the vector.
 * @param self The location in memory to store the created vector.
 *
 * @return Either "OKAY" or "MALLOC_ERROR".
 */
enum Error vector_create(
        struct Vector* self, size_t element_size, void (*destroy)(void*));

/**
 * @brief Deletes a vector.
 *
 * @param self The location in memory of the vector that is about to be
 * destroyed.
 */
void vector_delete(struct Vector* self);

/**
 * @brief Push an element onto the end of the vector.
 *
 * In case of error, no change is made to the vector.
 *
 * @param self The vector being pushed onto.
 * @param element The element being pushed onto the vector.
 *
 * @return Either "OKAY" or "MALLOC_ERROR"
 */
enum Error vector_push(struct Vector* self, const void* element);

/**
 * @brief Pop the last element from the end of the vector. This will not resize
 * the vector.
 *
 * @param self The vector being popped from.
 * @param value The location in memory to store the value after it is popped.
 *
 * @return Either "OKAY" or "RANGE_ERROR"
 */
enum Error vector_pop(struct Vector* self, void* value);

/**
 * @brief Inserts an element into the vector at a given position.
 *
 * @param self The vector being inserted into.
 * @param index The index in the vector that the element should have once
 * inserted.
 * @param element The element being inserted into the vector.
 *
 * @return Either "OKAY", "MALLOC_ERROR" or "RANGE_ERROR"
 */
enum Error vector_insert(
        struct Vector* self, size_t index, const void* element);

// remove element from vector at given position
/**
 * @brief Remove element from the vector at given position.
 *
 * @param self The vector being removed from.
 * @param index The index of the element to remove.
 * @param value The location in memory to store the value after it is removed.
 *
 * @return Either "OKAY" or "RANGE_ERROR"
 */
enum Error vector_remove(struct Vector* self, size_t index, void* value);

// remove element from vector at given position, replacing it with the last
// element of the vector
enum Error vector_swap_remove(struct Vector* self, size_t index);

#endif
