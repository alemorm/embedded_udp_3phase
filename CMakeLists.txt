# Minimum CMake version required to generate
# our build system
cmake_minimum_required(VERSION 3.0)

# Name of our Project and specify it is a C only project
project(threephasepower C)

# Change the output dir for the executables to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add_executable creates executables with
# the given name. In our case it is "threephasegenerator"
# and "threephaseforwarder" source files are given as parameters. 
add_executable(threephasegenerator src/threephasegenerator.c)
add_executable(threephaseforwarder src/threephaseforwarder.c)

# Link the math.h library
target_link_libraries(threephasegenerator PRIVATE m)
