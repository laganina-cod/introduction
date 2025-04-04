cmake_minimum_required(VERSION 3.10)

# Название проекта
project(mxv_1d)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исполняемого файла
add_executable(mxv_1d mxv_1d.cpp)

# Включение поддержки OpenMP (если используется)
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(mxv_1d PRIVATE OpenMP::OpenMP_CXX)
endif()