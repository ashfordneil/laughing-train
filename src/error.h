/**
 * @file error.h
 * @author Neil Ashford
 * @date 5 March 2017
 */

#ifndef _LT_ERROR_
#define _LT_ERROR_

/**
 * @brief Representation of the error codes outputted by laughing_train
 * functions.
 */
enum Error {
    /// No error has occured.
    OKAY,
    /// Malloc (or calloc, realloc, etc) returned an error.
    MALLOC_ERROR,
    /// Attempting to access an element in a list that is out of range.
    RANGE_ERROR,
};

#endif
