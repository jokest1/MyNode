
file(GLOB SOURCES "src/*cpp")
set(SUB_NAME "AsyncReadAndSend")
set(LIB_END "lib")
set(LIB_NAME ${SUB_NAME}_${LIB_END})

message(${LIB_NAME})

add_library(${LIB_NAME} STATIC ${SOURCES})

target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)