# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(PO_Projekt)

# Specify the C++ standard (C++17 is recommended, change if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/entities/*.cpp"
    "src/entities/plants/*.cpp"
    "src/entities/animals/*.cpp"
)

# Add all the source files (.cpp) and header files (.hpp) to the executable.
# Including the headers is optional for CMake to build, but it helps IDEs
# (like VS Code or CLion) display them in the project explorer.
add_executable(main ${SOURCES})

# 1. Add compile options (-Wall, -g, -fsanitize=address)
target_compile_options(main PRIVATE
    -Wall
    -g
    -fsanitize=address
    -pg
)

# 2. Add link options (needed for address sanitizer)
target_link_options(main PRIVATE
    -fsanitize=address
)

target_include_directories(main PRIVATE
    "src"
    "src/entities"
    "src/entities/plants"
    "src/entities/animals"
)

# 3. Link libraries (ncursesw)
target_link_libraries(main PRIVATE ncursesw)