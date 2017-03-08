#include <vector.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tests the vector_create function.
 */
void test_create() {
    struct Vector vector;
    vector_create(&vector, sizeof(int), NULL);

    vector_delete(&vector);
}

/*
 * Tests the vector push function.
 */
void test_push() {
    struct Vector vector;
    vector_create(&vector, sizeof(int), NULL);

    for (int i = 0; i < 5; ++i) {
        vector_push(&vector, &i);
        assert(vector.capacity >= vector.size);
    }

    int* array = vector.data;
    for (int i = 0; i < 5; ++i) {
        assert(i == array[i]);
    }

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
    } else {
        fprintf(stderr, "Invalid argument.\n");
        return 2;
    }

    return 0;
}
