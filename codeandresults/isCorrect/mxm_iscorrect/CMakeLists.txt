cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MXMFunctionTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление исполняемого файла
add_executable(MXM_1D mxm_correct_1d.cpp)
add_executable(MXM_2D mxm_correct_2d.cpp)