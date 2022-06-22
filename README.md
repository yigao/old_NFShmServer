简体中文

<p align="right">当前版本: <strong>v1.0.0</strong></p>
<p align="center"><img src="https://github.com/yigao/NFShmServer/blob/master/doc/logo.png" alt="nfshmserver" width="300"/></p>
NFShmServer 是一个使用C++开发的轻量级,敏捷型,弹性的,分布式的共享内存的插件开发框架, 让你更快更简单的开发服务端应用. 部分思路来自UE4和Ogre.(当前主要用在游戏领域) 我写的开源架构，前几年开源过，后来自己做项目，又没开源了，现在没搞项目了，加上修改了2年了，打算重新开源

## 特性

- 可以做到分布式架构不需要修改任何源码的情况下，做到单进程运行，加快平时的服务器开发。分布式运行只需要程序启动是参数修改即可
- C++热更，服务器崩溃后重启，玩家无感知，无影响，不丢任何物价数据，甚至连内网协议数据都不会有丢失，游戏数据均放在共享内存里，共享内存架构经过很多MMO大项目验证无问题，内网通讯采用共享内存通讯的话，服务器异常时，玩家协议数据不会丢失。如果你水平足够的话，理论上还可以做到服务器不重启so热更，当然不建议你这么做。
- 服务器游戏配置数据，从excel到共享内存代码，到sql语句，只需定义一个protobuf结构，就可以生成大量有用代码，你可以用这个protobuf结构去读取excel数据，生成对应的共享内存结构类，来存放数据，也可以生成sql数据，把excel表导入到数据库，不需要修改源码，可以从本地文件读取excel数据，可以直接从数据库读取配置。
- 玩家个人数据，只需定义一个protobuf结构，自动生成共享内存数据，sql数据，通过protobuf发射来完成mysql数据的存取，无需你自己写sql语句。
- 类似腾讯内部服务器，每一个服务器进程都有一个独立的类似网络IP的ID，来代表这个服务器，你不需要知道任何一个服务器进程部署在哪里，只要知道这个服务器的独立ID，就可以相互通讯
- 友好的日志控制，你可以单独控制，一个小模块的日志，甚至一个玩家的日志
- 跨平台(Windows, Linux, MacOS)
- 高可用的系统架构
- 高并发和高性能的网络模块
- 配套的 U3D 客户端，一个捕鱼项目，暂时没有上传
- 丰富的插件(DB, script, HTTP, WebSocket 等)

## Dependencies

- libevent
- spdlog
- google protobuf
- hiredis
- rapidjson
- concurrentqueue
- RapidXML
- LuaIntf
- navigation
- lua
- mysql
- mysqlpp
- curl
- evpp
- openssl
- theron
- zookeeper

## IF YOU CAN NOT BUILD THE DEPENDENCIES THEN PLEASE RUN THE CMDS BELOW TO SET UP THE ENVIRONMENT:

* sudo apt-get install g++
* sudo apt-get install cmake
* sudo apt-get install automake
* sudo apt-get install zip unzip

## 如果你需要编译makefile，用来编译excel，编译protobuf，用来生成代码解析excel, 并生成能放在共享内存里的代码
* 请参考文档https://github.com/yigao/NFShmServer/blob/master/doc/README.md, 安装需要的protobuf库

## Supported Compilers

* GCC >= 7 (**Tested on Centos 7**)

## Build and Install
### FOR LINUX(UBUNTU, CENTOS) ---- please use administrator(or sudo) to do these:
1. Git pull all source
2. Run **build_dynamic_debug.sh** to build Debug of NFShmServer
3. Run **build_dynamic_release.sh** to build Release of NFShmServer
4. Run the server， 分几种情况执行:
    - 根据使用master服务器来做分布式还是使用zookpeer，需要先配置好zookpeer，分几种种执行方式：
    -  如果你想把所有的分布式进程放到一个进程一个线程里执行的话，只要是方便调试:
    -    内网使用TCP通信,master服务器来做分布式:./NFPluginLoader --Server=AllServer --ID=1.1.1.1 --Config=../../Config --Plugin=../../TcpPlugin --restart
    -    内网使用Bus通信,master服务器来做分布式:./NFPluginLoader --Server=AllServer --ID=1.1.1.1 --Config=../../Config --Plugin=../../BusPlugin --restart
    -    内网使用TCP通信,zookpeer服务器来做分布式:./NFPluginLoader --Server=AllServer --ID=1.1.1.1 --Config=../../Config --Plugin=../../TcpPlugin_Zookpeer --restart
    -    内网使用Bus通信,zookpeer服务器来做分布式:./NFPluginLoader --Server=AllServer --ID=1.1.1.1 --Config=../../Config --Plugin=../../BusPlugin_Zookpeer --restart
    - 如果你想分布式执行:
    -    内网使用TCP通信,master服务器来做分布式:执行脚本CreateScript.sh或CreateScript_TcpPlugin.sh，会生成Start.sh,Stop.sh,ReStart.sh,Alllog.sh等脚本，执行Start.sh，会一个一个启动服务器，执行Alllog.sh可以查看所有服务器的日志。
    -    内网使用Bus通信,master服务器来做分布式:执行脚本CreateScript_BusPlugin.sh，会生成Start.sh,Stop.sh,ReStart.sh,Alllog.sh等脚本，执行Start.sh，会一个一个启动服务器，执行Alllog.sh可以查看所有服务器的日志。
    -    内网使用TCP通信,zookpeer服务器来做分布式:执行脚本CreateScript_TcpPlugin_Zookpeer.sh，会生成Start.sh,Stop.sh,ReStart.sh,Alllog.sh等脚本，执行Start.sh，会一个一个启动服务器，执行Alllog.sh可以查看所有服务器的日志。
    -    内网使用Bus通信,zookpeer服务器来做分布式:执行脚本CreateScript_BusPlugin_Zookpeer.sh，会生成Start.sh,Stop.sh,ReStart.sh,Alllog.sh等脚本，执行Start.sh，会一个一个启动服务器，执行Alllog.sh可以查看所有服务器的日志。
      

#### 一些很赞的项目

[PSS](https://github.com/freeeyes/PSS)

- 作者: freeeyes
- 描述: 基于插件的跨平台网络服务器框架

[ARK](https://github.com/OpenArkStudio/ARK.git)

- 作者: NickYang1988
- 描述: 基于插件的跨平台网络服务器框架

[NoahGameFrame](https://github.com/ketoo/NoahGameFrame.git)

- 作者: ketoo
- 描述: 基于插件的跨平台网络服务器框架
