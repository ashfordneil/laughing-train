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

    array = vector.data;
    for (int i = 0; i < 5; ++i) {
        assert(i == array[i]);
    }

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
    }

    error = vector_pop(&vector, NULL);
    assert(error == RANGE_ERROR);

    vector_delete(&vector);
}

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
    } else {
        fprintf(stderr, "Invalid argument.\n");
        return 2;
    }

    return 0;
}
