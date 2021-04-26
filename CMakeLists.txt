cmake_minimum_required(VERSION 2.6)
project(a_star)

# .cpp files
set(MY_PROGRAM_REQUIRED_FILES
    src/main.cpp
    src/map_utils.cpp
    src/a_star.cpp
)

include_directories(include)

# executable
add_executable(a_star ${MY_PROGRAM_REQUIRED_FILES})

install(DIRECTORY include/
  DESTINATION include/
)