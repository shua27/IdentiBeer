cmake_minimum_required(VERSION 3.7)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)

project(Identibeer)

include_directories(${src})

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(DisplayImage src/main.cpp)
target_link_libraries(DisplayImage ${OpenCV_LIBS})


