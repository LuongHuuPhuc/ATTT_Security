set(source_file "des.c")

add_library(DES_lib STATIC ${source_file})

target_include_directories(DES_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DES_lib)