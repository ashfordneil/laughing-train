add_executable(vector vector.c)
target_link_libraries(vector laughing_train)

add_test(vector_create ./vector CREATE)
add_test(vector_push ./vector PUSH)
