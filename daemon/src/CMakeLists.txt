cmake_minimum_required(VERSION 3.25)
project(daemon)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS DBus)
SET(CMAKE_AUTOMOC ON)

file(GLOB srcs daemon.cpp main.cpp)

qt_add_dbus_interface(srcs
        open-with.xml
        register_interface
)
qt_add_dbus_adaptor(srcs
        open-with.xml
        qobject.h
        "" # empty parent_class value on purpose to not pass -l flag
        register_adaptor
)

add_executable(daemon ${srcs})
target_link_libraries(daemon PRIVATE Qt6::DBus)
