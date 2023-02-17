cmake_minimum_required(VERSION 3.20)
project(CppFiles)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CppFiles
        "evm/easy.cpp"
        "evm/cache.cpp"
        "LOSH2021/heavy-light decomposition.cpp"
        "LOSH2021/suff-mas.cpp"
)
