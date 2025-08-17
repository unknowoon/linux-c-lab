cmake_minimum_required(VERSION 3.10)
project(linux-c-lab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# Logger library
add_library(logger STATIC
    logger/logger.c
    logger/logger.h
        linked_list/linked_list.c
)
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/logger)

# Logger test executable
add_executable(test_logger logger/test_logger.c)
target_link_libraries(test_logger logger)

# My string library
add_library(my_string STATIC
    my_string/my_memchr.c
    my_string/my_memcmp.c
    my_string/my_memcpy.c
    my_string/my_memmove.c
    my_string/my_memset.c
    my_string/my_strcat.c
    my_string/my_strchr.c
    my_string/my_strcmp.c
    my_string/my_strcpy.c
    my_string/my_strcspn.c
    my_string/my_strlen.c
    my_string/my_strncmp.c
    my_string/my_strncpy.c
    my_string/my_strpbrk.c
    my_string/my_strrchr.c
    my_string/my_strspn.c
    my_string/my_strstr.c
    my_string/my_strtok.c
)
target_include_directories(my_string PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/my_string)