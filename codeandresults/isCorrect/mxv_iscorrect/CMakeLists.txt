cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MXVFunctionTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление исполняемого файла
add_executable(MXV_1D mxv_correct_1d.cpp)
add_executable(MXV_2D mxv_correct_2d.cpp)
