cmake_minimum_required(VERSION 3.7)

project(Femto)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB Femto_SRC
    "src/*.c"
    "src/*/*.c"
)

file(GLOB Femto_INC
    "include/*.h"
    "include/*/*.h"
)

add_executable(Femto ${Femto_SRC} ${Femto_INC})
target_link_libraries(Femto ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
