cmake_minimum_required(VERSION 3.24)
project(bufreader C)

set(CMAKE_C_STANDARD 17)

add_library(bufreader lib/bufreader.c)
