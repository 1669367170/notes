# CMake
## 一、cmake_tutorial_a
参考链接：
- [全网最细的CMake教程！(强烈建议收藏)](https://zhuanlan.zhihu.com/p/534439206)  
- [Code](https://github.com/wzpan/cmake-demo)

### 1. 什么是CMake？
- "Write once, run everywhere"
- <mark>允许开发者编写一种平台无关的 CMakeList.txt 文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化 Makefile 和工程文件；</mark>
- 解决多种Make工具（GNU Make、QT的qmake，微软的MS nmake，BSD的Make(pmake)、Makepp等）无法跨平台编译的问题。
- CMake 是一个比上述几种 make 更高级的编译配置工具。在Linux平台使用CMake生成Makefile并编译的流程：
   ```
   （1）写 CMake 配置文件 CMakeLists.txt；
   （2）执行命令 cmake PATH 或者 ccmake PATH 生成 Makefile（ccmake 和 cmake 的区别在于前者提供了一个交互式的界面）。其中， PATH 是 CMakeLists.txt 所在的目录；
   （3）使用 make 命令进行编译。
   ```
### 2. 入门案例：单个源文件
- 文件目录树  
![Alt text](image.png)
- 编写CMakeLists.txt
  ```
  # CMake 最低版本号要求
  cmake_minimum_required (VERSION 2.8)
  # 项目信息
  project (Demo1)
  # 指定生成目标
  add_executable(Demo main.cc)
  ```
- 生成MakeFile、编译、执行
    ```
    cmake .. -G "MinGW Makefiles" # 生成MakeFile(win10环境)
    mingw32-make.exe -j8 # 编译
    ./CMake_Demo.exe 5 3 # 执行
    ```
### 3. 多个源文件
#### 3.1 同一目录，多个源文件
- 文件目录树
  ```
  ./Demo2
    |
    +--- main.cc
    |
    +--- MathFunctions.cc
    |
    +--- MathFunctions.h
  ```
- 编写CMakeLists.txt
  ```
  # CMake 最低版本号要求\
  cmake_minimum_required (VERSION 2.8)
  # 项目信息
  project (Demo2)
  # 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
  aux_source_directory(. DIR_SRCS)
  # 指定生成目标
  add_executable(Demo ${DIR_SRCS})
  ```
  <mark>查找指定目录下的所有源文件，然后将结果存进指定变量名：`aux_source_directory(<dir> <variable>)`</mark>
#### 3.2 多个目录，多个源文件、
- 文件目录树
  ```
  ./Demo3
    |
    +--- main.cc
    |
    +--- math/
          |
          +--- MathFunctions.cc
          |
          +--- MathFunctions.h
  ```
- 编写CMakeLists.txt  
  <mark>项目根目录 Demo3 和 math 目录里各编写一个 CMakeLists.txt 文件，先将 math 目录里的文件编译成静态库再由 main 函数调用</mark>  


  （1）根目录下
    - 使用命令 add_subdirectory 指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理
  ```
  # CMake 最低版本号要求
  cmake_minimum_required (VERSION 2.8)
  # 项目信息
  project (Demo3)

  # 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
  aux_source_directory(. DIR_SRCS)

  # 添加 math 子目录
  add_subdirectory(math)

  # 指定生成目标 
  add_executable(Demo main.cc)

  # 添加链接库
  target_link_libraries(Demo MathFunctions)
  ```
  （2）math目录下
  - 使用命令 add_library 将 src 目录中的源文件编译为静态链接库。
  ```
  # 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
  aux_source_directory(. DIR_LIB_SRCS)
  
  # 生成链接库
  add_library (MathFunctions ${DIR_LIB_SRCS})
  ```
### 4. 自定义编译选项
