cmake_minimum_required(VERSION 3.14)
project(Linpop C)

set(CMAKE_C_STANDARD 99)

add_executable(server server/main.c common/srcs/socket_utils.c common/srcs/rio.c)

add_executable(client client/main.c common/srcs/socket_utils.c common/srcs/rio.c)
add_executable(IO_MUX_TEST test/IO_MUX_test.c common/srcs/socket_utils.c common/srcs/rio.c)
add_executable(echoclient test/client.c common/srcs/socket_utils.c common/srcs/rio.c)

include_directories(/common/include/)

target_link_libraries(server pthread)