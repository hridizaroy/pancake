cmake_minimum_required(VERSION 3.21.1)
set(CMAKE_BUILD_TYPE Release)

project(pancake)

set(SRC
    src/pancake.cpp    
)

set( OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/opencv/build )

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories( ${OpenCV_LIB_DIR} )

add_executable(pancake ${SRC})
target_link_libraries(pancake ${OpenCV_LIBS})