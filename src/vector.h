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
    /// The total capacity of the vector.
    size_t capacity;
    /// The number of elements currently stored in the vector.
    size_t size;
    /// The actual data stored in the vector.
    void** data;
};

// copies a vector
enum Error vector_copy(struct Vector* output, const struct Vector* input);

/**
 * @brief Creates a new vector.
 *
 * @param parameter The location in memory to store the created vector.
 *
 * @return Either "OKAY" or "MALLOC_ERROR".
 */
enum Error vector_create(struct Vector* parameter, void (*destroy)(void*));

/**
 * @brief Deletes a vector.
 *
 * @param parameter The location in memory of the vector that is about to be
 * destroyed.
 */
void vector_delete(struct Vector* parameter);

/**
 * @brief Push an element onto the end of the vector.
 *
 * In case of error, no change is made to the vector.
 *
 * @param parameter The vector being pushed onto.
 * @param element The element being pushed onto the vector.
 *
 * @return Either "OKAY" or "MALLOC_ERROR"
 */
enum Error vector_push(struct Vector* parameter, void* element);

// remove last element of vector
void vector_pop(struct Vector* parameter);

// insert element into vector at given position
enum Error vector_insert(
        struct Vector* parameter, size_t index, void* element);

// remove element from vector at given position
enum Error vector_remove(struct Vector* parameter, size_t index);

// remove element from vector at given position, replacing it with the last
// element of the vector
enum Error vector_swap_remove(struct Vector* parameter, size_t index);

#endif
