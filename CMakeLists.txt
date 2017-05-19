cmake_minimum_required(VERSION 3.7)
project(untitled1)

include_directories(${src})

project( DisplayImage )
find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(DisplayImage src/main.cpp)
target_link_libraries(DisplayImage ${OpenCV_LIBS})



set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(CapTure ${SOURCE_FILES})