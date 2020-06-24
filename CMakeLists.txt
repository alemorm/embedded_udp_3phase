# Minimum CMake version required to generate
# our build system
cmake_minimum_required(VERSION 3.0)

# Name of our Project and specify it is a C only project
project(threephasepower C)

# Change the output dir for the executables to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add_executable creates an executable with
# the given name. In our case it is "threephasepower"
# source files are given as parameters. In our
# case we only have one source file threephasegenerator.c
add_executable(threephasepower src/threephasegenerator.c)

# Link the math.h library
target_link_libraries(threephasepower PRIVATE m)
