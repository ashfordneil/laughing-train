add_executable(vector vector.c)
target_link_libraries(vector laughing_train)

add_test(vector_create ./vector CREATE)
add_test(vector_push ./vector PUSH)
add_test(vector_pop ./vector POP)
add_test(vector_insert ./vector INSERT)
add_test(vector_remove ./vector REMOVE)
add_test(vector_swap_remove ./vector SWAP_REMOVE)