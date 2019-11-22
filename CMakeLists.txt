cmake_minimum_required(VERSION 3.10)

# set the project name
project(tp2)

file(GLOB_RECURSE src
    "src/*.h"
    "src/*.c"
)

file(GLOB_RECURSE tests
    "tests/*.h"
    "tests/*.c"
)

# add the executable
add_executable(tp2 ${src} main/main.c)

# add the executable
add_executable(pruebas ${src} ${tests})

set_property(TARGET tp2 PROPERTY C_STANDARD 11)
