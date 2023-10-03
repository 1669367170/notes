# 新手指南
## 1. 权限  
### 1.1 root权限设置
```
sudo passwd root # 给root用户设置密码
su root # 切换到root用户
exit # 退出
```
## 2. 常用软件下载和运行
### 2.1 软件下载方式   
> 方式一：通过Ubuntu Software下载   
> 方式二：
> - apt-get # 系统自带   apt-get -v
> - apt # 系统自带   
查找(search)；下载(update)；安装(install)；升级(upgrade)；例：apt search   
> - aptitude # 需要自行安装 sudo apt install aptitude

### 2.2 软件下载路径查看   
> - 直接查看   
> Ubuntu Software下载的地方：   
> 方式一：Ubuntu Software -> 已安装;   
> 方式二：计算机 -> snap;
> - 检索查看   
`sudo find / -name code`
- 软件使用root权限执行   
例：运行vscode
```
su root
cd /snap/bin
./code --no-sandbox --user-data-dir
```

## 3. 网络代理
Q1: ubuntu上解决访问github慢的方法   
https://blog.csdn.net/c_w_l/article/details/130398320   

modify hosts files method: 
```
1. Get the ip:
nslookup github.global.ssl.fastly.Net
nslookup github.com

2. Open the hosts file:
sudo vim /etc/hosts or sudo gedit /etc/hosts

3. Add following two lines to the hosts file's ending:

github.com 20.205.243.166
github.global.ssl.fastly.Net 31.13.94.41

4. Update dns caches: 
sudo resolvectl flush-caches
```


Q2: ubuntu不能使用google搜索

- 代理设置方式
方式一：设置 -> 网络 -> 网络代理 -> http代理等都默认，http代理端口号是8080


## 4. 查看系统信息
### 4.1 查看 cpu 信息
```
# CPU型号
cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c

# 物理 CPU 个数
cat /proc/cpuinfo| grep "physical id"| sort| uniq| wc -l

# CPU核数 (物理CPU个数 * 每个CPU的核数)
cat /proc/cpuinfo| grep "cpu cores"| uniq

# 逻辑CPU个数 (物理CPU个数 * 每个CPU的核数 * 超线程数)
cat /proc/cpuinfo| grep "processor"| wc -l
```
### 4.2 查看操作系统信息
```
# 查看操作系统内核信息
uname -a

# 查看操作系统发行版本
cat /etc/issue
lsb_release -a

# 查看hostname
hostname

# 网卡信息
ip a
```

---
## 参考链接
> [1] Ubuntu安装Chrome
https://zhuanlan.zhihu.com/p/626211516   
