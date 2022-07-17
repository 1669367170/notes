# Geos库

官网链接：https://libgeos.org/usage/c_api/

官网使用说明指导：https://libgeos.org/doxygen/geos__c_8h.html#details

github仓链接：https://github.com/libgeos/geos

## 1. win10、mingw编译构建geos库

参考构建链接：

https://www.cnblogs.com/oloroso/p/6762624.html

步骤：

> a. 在官网https://libgeos.org/usage/download/  下载geos源码；（官网也有构建说明）
>
> b. 解压源码后，在解压后的目录下，mkdir build -> cd build；
>
> c. cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=安装路径
>
> 【注】：cmake -G的G应该是Generator的意思，该语句可以设置IDE，比如Xcode。cmake -D 是用来设置编译器的
>
> d. 通过步骤c以后生成了Makefile；
>
> e. 编译和安装；
>
> 编译： mingw32-make -f Makefile
>
> 安装： mingw32-make -f Makefile install
>
> 【注】make命令会首先在当前目录查找名为makefile的文件，如果找不到，就会查找名为Makefile的文件。
>
> 为了指示make命令将哪个文件作为makefile文件，可以使用 -f 选项。
