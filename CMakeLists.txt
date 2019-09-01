cmake_minimum_required(VERSION 3.10.3)
project(Linpop C)

set(CMAKE_C_STANDARD 99)

add_executable(server server/main.c common/srcs/socket_utils.c common/srcs/rio.c server/login_on_server.h server/login_on_server.c)

add_executable(client common/srcs/socket_utils.c common/srcs/rio.c client/UI/Chat/chat.c client/UI/Chat/list.c client/UI/Chat/main.c)



include_directories(/common/include/)

target_link_libraries(server pthread)
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-2.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

TARGET_LINK_LIBRARIES(client ${GTK3_LIBRARIES})