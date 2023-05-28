# vscode使用mingw和cmake编写和运行C++ OpenCV程序

## 一、相关软件安装&环境搭建

### 1. mingw

- 下载链接：https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/

  直接下载链接：https://sourceforge.net/projects/mingw-w64/files/mingw-w64/

- 参考安装链接：https://blog.51cto.com/xiaohaiwa/5381183

  - 选择电脑系统架构：电脑系统是 64位的，选择 **x86_64**；如果是 32位 系统，则选择 i686 即可。

  - 选择操作系统接口协议：如果你想要开发 Windows 程序，需要选择 win32 ，**而开发 Linux、Unix、Mac OS 等其他操作系统下的程序，则需要选择 posix 。**

  - 选择异常处理模型（64位）：异常处理在开发中非常重要，在开发的过程中，大部分的时间会耗在处理各种异常情况上。seh 是新发明的，而 sjlj 则是古老的。seh 性能比较好，但不支持 32位。 sjlj 稳定性好，支持 32位。**建议64位操作系统选择seh。**

- 高级系统配置->环境变量Path添加mingw64的bin目录

### 2. cmake

- 官网链接：https://cmake.org/download/

- vscode配置

  在代码目录下将工作区另存为，得到xx.code-workspace文件，内容填写如下（主要是cmake.generator）

  >{
  >
  >  "folders": [
  >
  >​    {
  >
  >​      "path": "."
  >
  >​    }
  >
  >  ],
  >
  >  "settings": {
  >
  >​    "files.associations": {
  >
  >​      "iostream": "cpp",
  >
  >​      "cfloat": "cpp",
  >
  >​      "vector": "cpp"
  >
  >​    },
  >
  >​    "cmake.generator": "MinGW Makefiles" // 添加这一行
  >
  >  }
  >
  >}
  >
  >

### 3. opencv

- 下载链接：https://sourceforge.net/projects/opencvlibrary/files/

- 构建和编译

  参考链接：https://www.cnblogs.com/oloroso/p/6762624.html

  （1）解压源码后，在解压后的目录下执行

  > mkdir build_install
  >
  > cd build_install

  （2）生成Makefile

  > cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=安装路径
  >
  > （注：-G设置编译器）

  （3）编译和安装

  - 编译

    > mingw32-make -f Makefile

  - 安装

    > mingw32-make -f Makefile install

  【注】make命令会首先在当前目录查找名为makefile的文件，如果找不到，就会查找名为Makefile的文件。

  为了指示make命令将哪个文件作为makefile文件，可以使用 -f 选项。

- cmakeList配置

  > cmake_minimum_required(VERSION 3.15)
  >
  > project(test)
  >
  > 
  >
  > // 寻找opencv库，有OpenCVConfig.cmake文件的地方
  >
  > set(OpenCV_DIR /xxx/opencv-4.5.2/build_install)
  >
  > find_package(OpenCV 4 REQUIRED)
  >
  > // 添加头文件
  >
  > include_directories(${OpenCV_INCLUDE_DIRS})
  >
  > 
  >
  > add_executable(test main.cpp)
  >
  > // link_libraries
  >
  > // 链接OpenCV库
  >
  > target_link_libraries(test ${OpenCV_LIBS})

---

## 二、vscode安装相应扩展

- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)：微软出品的用于 VSCode 的 C/C++ 扩展。

  会自带安装Clang-format格式化插件：C:\Users\xxx\.vscode\extensions\ms-vscode.cpptools-1.15.4-win32-x64\LLVM\bin

  快捷键：Alt+Shift+F

- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)：微软出品的用于 VSCode 的 CMake 工具扩展。

- （可选）[CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)：这个我主要是用他的语法高亮，CMake Tools 没有提供 CMakeLists.txt 的语法高亮，看着不太得劲。

---

## 三、编译和执行程序

在对应代码目录下，执行以下命令：

> mkdir build -> cd build -> cmake .. -G "MinGW Makefiles" -> mingw32-make.exe -> 对应build目录下会生成exe可执行文件

---

## 四、可能遇到的问题

- Q1：cmake .. 报错

  Solve：**cmake .. -G "MinGW Makefiles"**

![cmake q1](D:\01-study\02-env_build\cmake q1.png)



---

