cmake_minimum_required(VERSION 3.27)
project(lab4 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCES
        src/entity.c
        src/repository.c
        src/validator.c
        src/service.c
        src/console.c
        src/tests.c
        src/main.c
)

add_executable(lab4 ${SOURCES})

target_include_directories(lab4
        PUBLIC include
)