# 1. Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# 2. Project name and language
project(promon CXX)

# 3. Use C++17 standard (industry standard for modern logic)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Add the executable: (Output Name) (Source Files)
add_executable(promon main.cpp)

# 5. [Optional] On Linux, some low-level features require the 'pthread' library
if(LINUX)
    target_link_libraries(promon pthread)
endif()

# Use CMAKE_SYSTEM_NAME to be explicit
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(promon pthread)
endif()