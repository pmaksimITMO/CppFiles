cmake_minimum_required(VERSION 3.20)
project(CppFiles)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

include_directories(.)

add_executable(CppFiles
#        "evm/easy.cpp"
#        "evm/cache.cpp"
#        "LOSH2021/heavy-light decomposition.cpp"
#        "LOSH2021/suff-mas.cpp"
#        "Yandex trainings 3.0/Beautiful_String.cpp"
#        A&DS/SegTree/RMQ.cpp
#        A&DS/SegTree/PermutationOnSeg.cpp
#        "Yandex trainings 3.0/ContestBackend_A.cpp"
#        "Yandex trainings 3.0/ContestBackend_B.cpp"
#        "Yandex trainings 3.0/ContestBackend_C.cpp"
#        "Yandex trainings 3.0/ContestBackend_D.cpp"
#        "Yandex trainings 3.0/ContestBackend_stupid_solve.cpp"
#        DMlabs/Test2.cpp
        CppCourse/substring.cpp
        )
