cmake_minimum_required(VERSION 3.8)
project(thunnel VERSION 0.1.0)

include(CTest)
enable_testing()



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

INCLUDE_DIRECTORIES(include)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

set(SOURCE_FILES ${DIR_SRCS})
add_executable(${PROJECT_NAME} main.cpp  ${SOURCE_FILES})

find_package(libuv CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>)
