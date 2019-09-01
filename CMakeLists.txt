cmake_minimum_required(VERSION 3.10.3)
project(Linpop C)

set(CMAKE_C_STANDARD 99)

add_executable(server server/main.c common/srcs/socket_utils.c common/srcs/rio.c server/login_on_server.cpp server/login_on_server.h)

add_executable(client client/main.c common/srcs/socket_utils.c common/srcs/rio.c)



include_directories(/common/include/)

target_link_libraries(server pthread)