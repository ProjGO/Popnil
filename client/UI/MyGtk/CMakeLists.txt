cmake_minimum_required(VERSION 3.10)
project(MyGtk)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyGtk main.c login.c sign.c sign_success.c set_background.c chat.c)


FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-2.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

TARGET_LINK_LIBRARIES(MyGtk ${GTK3_LIBRARIES})
