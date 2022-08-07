cmake_minimum_required(VERSION 3.15)
set(project_name Google_Test_Examples)
project(${project_name})
set(CMAKE_CXX_STANDARD 14)

#set(GOOGLE_TEST_DIR D:/kqz/6_OpenSource/googletest-main)
#set(GOOGLE_TEST_INC D:/kqz/6_OpenSource/googletest-main/googletest/include)
#set(GOOGLE_MOCK_INC D:/kqz/6_OpenSource/googletest-main/googlemock/include)

set(GOOGLE_TEST_INC D:/kqz/6_OpenSource/googletest-main/install/include)
set(GOOGLE_TEST_LIB D:/kqz/6_OpenSource/googletest-main/install/lib)

## 编译google test，会在当前目录生成libtest.a静态库
#add_subdirectory(./googletest-main)

# 递归搜索
#file(GLOB_RECURSE CXX_SRCS "*.cpp")
aux_source_directory(. CXX_SRCS)
# 当前目录所有源文件的文件名赋值给变量 CXX_SRCS
message(STATUS "cppfiles: " ${CXX_SRCS})

#include_directories(${GOOGLE_TEST_INC})
link_directories(${GOOGLE_TEST_LIB})
add_executable(${project_name} ${CXX_SRCS})

# 添加头文件所在目录
target_include_directories(
        ${project_name}
        PUBLIC
        ${GOOGLE_TEST_INC})

target_link_libraries(
        ${project_name}
        libgtest.a
        libgtest_main.a
        libgmock.a
        libgmock_main.a)
