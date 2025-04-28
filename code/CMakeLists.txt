cmake_minimum_required(VERSION 3.10)
project("Test Code")


# test 测试camke是否能生成lib文件
# ClientAndSever 测试简单的服务器和客户端连接

set(MODEL_NAME "AsyncSever")

# 条件编译

if(${MODEL_NAME} STREQUAL  "test")
    set(HEAD_DIR_NAME "test")
elseif(${MODEL_NAME} STREQUAL  "ClientAndSever")
    set(HEAD_DIR_NAME "ClientAndSever")
elseif(${MODEL_NAME} STREQUAL  "ReadAndWrite")
    set(HEAD_DIR_NAME "ReadAndWrite")
elseif(${MODEL_NAME} STREQUAL  "AsyncReadAndSend")
    set(HEAD_DIR_NAME "AsyncReadAndSend")
elseif(${MODEL_NAME} STREQUAL  "AsyncSever")
    set(HEAD_DIR_NAME "AsyncSever")
endif()


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
        wsock32
)
        
