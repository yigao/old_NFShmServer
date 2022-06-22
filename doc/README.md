## 安装google python模块(需要安装python2.7, centos7自带)
- 解压thirdparty/pkg目录下得protobuf-2.5.0.tar, 会有一个protobuf-2.5.0目录，里面有protobuf的源文件, cd protobuf-2.5.0
- 编译protobuf,执行:
- ./configure
- make
- make install
- 在protobuf-2.5.0目录下有一个python目录，执行下面命令:
- cd python 
- python setup.py build 
- python setup.py test 
- python setup.py install
- 验证Python模块，执行python
- python 
>>> import google.protobuf.internal
>>> 
验证Python模块是否被正确安装
如果没有报错，说明安装正常。

## windows安装make, 执行tools/mingw-get-setup
- 安装MinGW的时候选择Basic setup下选择mingw32-base包就可以了。
- 打开MinGW的安装目录，打开bin文件夹，将mingw32-make.exe重命名为make.exe。
- 设置环境变量，只需把bin文件夹的路径放到用户变量中去。
