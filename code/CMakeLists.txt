cmake_minimum_required(VERSION 3.10)
project("Test Code")
# set(HEAD_DIR_NAME "test")

set(HEAD_DIR_NAME "ClientAndSever")

set(LIB_END "_lib")
# 添加子目录（会自动执行子目录的 CMakeLists.txt）
add_subdirectory(${HEAD_DIR_NAME})

add_executable(main 
    main.cpp
)
message(${HEAD_DIR_NAME}${LIB_END})
# 链接子目录生成的库
target_link_libraries(main 
    PRIVATE 
        ${HEAD_DIR_NAME}${LIB_END}  
        ws2_32
)