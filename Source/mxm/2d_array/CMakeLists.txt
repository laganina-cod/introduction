cmake_minimum_required(VERSION 3.10)

# Название проекта
project(mxm_2d)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исполняемого файла
add_executable(mxm_2d mxm_2d.cpp)

# Включение поддержки OpenMP (если используется)
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(mxm_2d PRIVATE OpenMP::OpenMP_CXX)
endif()