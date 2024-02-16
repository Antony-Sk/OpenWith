cmake_minimum_required(VERSION 3.25)
project(openwith)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(Qt6 REQUIRED COMPONENTS DBus)

file(GLOB srcs main.cpp)

add_executable(openwith ${srcs})
target_link_libraries(openwith PRIVATE Qt6::DBus)
