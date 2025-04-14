cmake_minimum_required(VERSION 3.30)
project(DES)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Them file thuc thi cua chuong chinh chinh
add_executable(des_main "DES_main/des_main.c")

# Them thu muc chua thu vien ben ngoai
add_subdirectory(DES_lib)

# Lien ket chuong chinh chinh voi thu vien ben ngoai
target_link_libraries(des_main PRIVATE DES_lib)