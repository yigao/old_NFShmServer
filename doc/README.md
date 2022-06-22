安装google python模块, 解压thirdparty/pkg目录下得protobuf-2.5.0.tar, 复制tools下面的protoc.exe到protobuf-2.5.0/src目录下,然后执行
cd python 
python setup.py build 
python setup.py test 
python setup.py install
验证Python模块
验证Python模块是否被正确安装
如果没有报错，说明安装正常。

$ python 
>>> import google.protobuf.internal
>>> 

windows安装make, 执行tools/mingw-get-setup
2、安装MinGW的时候选择Basic setup下选择mingw32-base包就可以了。
3、打开MinGW的安装目录，打开bin文件夹，将mingw32-make.exe重命名为make.exe。
4、设置环境变量，只需把bin文件夹的路径放到用户变量中去。