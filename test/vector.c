#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

/*
 * Tests the vector_create function and the vector_delete.
 */
void test_create()
{
    struct Vector vector;
    enum Error error;

    error = vector_create(&vector, sizeof(int), NULL);
    assert(error == OKAY);

    vector_delete(&vector);
}

/*
 * Tests the vector_push function.
 * Assumes working implementations of create and delete.
 */
void test_push()
{
    struct Vector vector;
    enum Error error;
    int* array;

    error = vector_create(&vector, sizeof(int), NULL);
    assert(error == OKAY);

    for (int i = 0; i < 5; ++i) {
        error = vector_push(&vector, &i);
        assert(error == OKAY);
        assert(vector.capacity >= vector.size);
    }
    assert(vector.size == 5);

    array = vector.data;
    for (int i = 0; i < 5; ++i) {
        assert(i == array[i]);    }

    vector_delete(&vector);
}

/*
 * Tests the vector_pop function.
 * Assumes working implementations of create, delete and push.
 */
void test_pop()
{
    struct Vector vector;
    enum Error error;

    error = vector_create(&vector, sizeof(int), NULL);
    assert(error == OKAY);

    for (int i = 0; i < 5; ++i) {
        error = vector_push(&vector, &i);
        assert(error == OKAY);
    }

    for (int i = 4, j; i >= 0; --i) {
        error = vector_pop(&vector, &j);
        assert(error == OKAY);
        assert(i == j);
        assert(vector.size == i);
    }

    error = vector_pop(&vector, NULL);
    assert(error == RANGE_ERROR);

    vector_delete(&vector);
}

/**
 * Test the vector_insert function.
 * Assumes working implementations of the create, delete and push functions.
 */
void test_insert()
{
    struct Vector vector;
    enum Error error;
    int* array;
    int x = 12;

    error = vector_create(&vector, sizeof(int), NULL);
    assert(error == OKAY);

    for (int i = 0; i < 5; ++i) {
        error = vector_push(&vector, &i);
        assert(error == OKAY);
    }

    error = vector_insert(&vector, 2, &x);
    assert(error == OKAY);
    assert(vector.size == 6);
    array = vector.data;

    assert(array[2] == x);
    for (int i = 0; i < 2; ++i) {
        assert(array[i] == i);
    }
    for (int i = 2; i < 5; ++i) {
        assert(array[i + 1] = i);
    }

    error = vector_insert(&vector, 12, &x);
    assert(error == RANGE_ERROR);

    vector_delete(&vector);
}

/**
 * Tests the vector_remove function.
 * Assumes working implementations of the create, delete and push functions.
 */
void test_remove()
{
    struct Vector vector;
    enum Error error;
    int* array;
    int x;

    error = vector_create(&vector, sizeof(int), NULL);
    assert(error == OKAY);

    for (int i = 0; i < 5; ++i) {
        error = vector_push(&vector, &i);
        assert(error == OKAY);
    }

    error = vector_remove(&vector, 2, &x);
    assert(error == OKAY);
    assert(x == 2);
    assert(vector.size == 4);

    array = vector.data;
    for (int i = 0; i < 2; ++i) {
        assert(array[i] == i);
    }
    for (int i = 2; i < 4; ++i) {
        assert(array[i] == i + 1);
    }

    error = vector_remove(&vector, 12, NULL);
    assert(error == RANGE_ERROR);

    vector_delete(&vector);
}

void test_swap_remove()
{
    struct Vector vector;
    enum Error error;
    int* array;
    int x;

    error = vector_create(&vector, sizeof(int), NULL);
    assert(error == OKAY);

    for (int i = 0; i < 5; ++i) {
        error = vector_push(&vector, &i);
        assert(error == OKAY);
    }

    error = vector_swap_remove(&vector, 2, &x);
    assert(error == OKAY);
    assert(x == 2);
    assert(vector.size == 4);

    array = vector.data;
    for (int i = 0; i < 2; ++i) {
        assert(array[i] == i);
    }
    assert(array[2] == 4);
    for (int i = 3; i < 4; ++i) {
        assert(array[i] == i);
    }

    error = vector_swap_remove(&vector, 12, NULL);
    assert(error == RANGE_ERROR);

    vector_delete(&vector);
}

void test_copy()
{
    struct Vector first, second;
    enum Error error;
    int* first_array;
    int* second_array;

    error = vector_create(&first, sizeof(int), NULL);
    assert(error == OKAY);

    for (int i = 0; i < 5; ++i) {
        error = vector_push(&first, &i);
        assert(error == OKAY);
    }
    first_array = first.data;

    error = vector_copy(&second, &first);
    assert(error == OKAY);
    
    second_array = second.data;
    for (int i = 0; i < 5; ++i) {
        assert(first_array[i] == second_array[i]);
    }

    vector_delete(&first);
    vector_delete(&second);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Argument not provided.\n");
        return 1;
    }

    if (!strcmp("CREATE", argv[1])) {
        test_create();
    } else if (!strcmp("PUSH", argv[1])) {
        test_push();
    } else if (!strcmp("POP", argv[1])) {
        test_pop();
    } else if (!strcmp("INSERT", argv[1])) {
        test_insert();
    } else if (!strcmp("REMOVE", argv[1])) {
        test_remove();
    } else if (!strcmp("SWAP_REMOVE", argv[1])) {
        test_swap_remove();
    } else if (!strcmp("COPY", argv[1])) {
        test_copy();
    } else {
        fprintf(stderr, "Invalid argument.\n");
        return 2;
    }

    return 0;
}
