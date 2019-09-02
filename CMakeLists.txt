cmake_minimum_required(VERSION 3.10.3)
project(Linpop C)

set(CMAKE_C_STANDARD 99)

add_executable(server server/main.c common/srcs/socket_utils.c common/srcs/rio.c server/login_reg_server.h server/login_reg_server.c
        server/friend_group_server.c server/friend_group_server.h server/database.c common/include/database.h server/)

add_executable(client client/chat.c client/list.c client/login.c client/main.c client/sign.c client/sign_success.c)

add_executable(client_chat common/srcs/socket_utils.c common/srcs/rio.c)



include_directories(/common/include/)

target_link_libraries(server pthread)
target_link_libraries(client_chat pthread)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
target_link_libraries(server libmysqlclient.so)
TARGET_LINK_LIBRARIES(client ${GTK3_LIBRARIES})