cmake_minimum_required(VERSION 2.6)

# .cpp files
set(MY_PROGRAM_REQUIRED_FILES
    main.cpp
    map_utils.cpp
    a_star.cpp
)

# executable
add_executable(a_star ${MY_PROGRAM_REQUIRED_FILES})

