cmake_minimum_required(VERSION 3.10.2)
project("myjniproject")

add_library(
        native-lib
        SHARED
        src/main/cpp/native-lib.cpp
)

find_library(log-lib log)
find_library(gles-lib GLESv2)

target_link_libraries(
        native-lib
        ${log-lib}
        ${gles-lib}
)
