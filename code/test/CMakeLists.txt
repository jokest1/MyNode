file(GLOB SOURCES "src/*.cpp")
set(SUB_NAME "test")
set(LIB_END "lib")

set(LIB_NAME ${SUB_NAME}_${LIB_END})

message(${LIB_NAME})

# 创建静态库/动态库
add_library(${LIB_NAME} STATIC ${SOURCES})

# 设置头文件目录（可选）
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  
)