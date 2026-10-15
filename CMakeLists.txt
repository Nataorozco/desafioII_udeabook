cmake_minimum_required(VERSION 3.16)
project(UdeABook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(UdeABook
    src/main.cpp
    src/fecha.cpp
    src/usuario.cpp
    src/mensaje.cpp
    src/album.cpp
    src/foto.cpp
    src/solicitudamistad.cpp
    src/redsocial.cpp
    include/nodo.h
    include/listaenlazada.h
)

# Los archivos de datos se leen desde la carpeta data/ del proyecto
target_compile_definitions(UdeABook PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
