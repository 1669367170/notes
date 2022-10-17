cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "leetcode")
project(${PROJECT_NAME})

option(PRINT_CMAKE_LOG "print cmake log" ON)

if (PRINT_CMAKE_LOG)
    message("--------------------------------")
    message(STATUS ${PROJECT_NAME}, " BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
endif (PRINT_CMAKE_LOG)

add_subdirectory(array)
add_subdirectory(back_tracking)

set(GOOGLE_TEST_INC ../thirdparty/googletest-main/install/include)
set(GOOGLE_TEST_LIB ../thirdparty/googletest-main/install/lib)

set(SRCs src/main.cpp)
list(APPEND SRCs Sort.cpp)

link_directories(${GOOGLE_TEST_LIB})

# 添加一个可执行程序
add_executable(${PROJECT_NAME} ${SRCs})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${GOOGLE_TEST_INC})

target_link_libraries(${PROJECT_NAME}
        array_lib
        back_tracking_lib
        libgtest.a
        libgtest_main.a
        libgmock.a
        libgmock_main.a)