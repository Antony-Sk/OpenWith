cmake_minimum_required(VERSION 3.25)
project(demo)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(../../include)

find_package(Qt6 REQUIRED COMPONENTS DBus)

add_executable(reg_handlers_demo main.cpp)
target_link_libraries(reg_handlers_demo Qt6::DBus)

