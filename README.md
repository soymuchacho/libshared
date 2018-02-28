![](https://github.com/soymuchacho/GitImage/raw/master/share.gif)
libshared
==============
    Lightweight multithreaded network library for Linux
Requirement
-----------------
* Linux 
* c++11 

Direectory Structure
---------------------------------
    |—— build                                       // 静态编译完成后的libshared.a，由make install命令安装在这里
    |—— 3rd                                         // 第三方库
    |—— examples                                    // 使用libshared的简单服务器例程
    |    |—— daytime                                // 时间核对服务器及客户端
    |    |—— echo                                   // echo服务器
    |    |—— time-task                              // 计时事件的使用例程
    |    |-- python-demo                            // python脚本加载及调用实例
    |    |-- ManagerServer                          // 企业管理软件服务器端实例
    |—— luaScript									// c++调用lua及lua调用c++接口支持
    |—— shared                                      // libshared的主体
    |    |—— common                                 // 网络基础库
    |    |—— network                                // 网络相关的封装
    |    |—— utility                                // 实用库
    |    |—— include                                // 头文件
    |    |—— db_mysql								// 对mysql的支持
    |    |—— pyscript								// c++调用python及python调用c++接口支持
    |    |—— src                                    // 原码cpp存放为值

Building & install
----------------------------------
	使用cmake
    $ cd libshared/shared
    $ cmake . 
    $ make 

	使用makefile
    $ cd libshared/shared
    $ make clean 
    $ make 
    $ make install
 
Wishes Extension
------------------------------------
	* suport mysql
    * suport python 
    * suport lua 
    * suport windows

Change Log
----------------------------------

    2016.9.22 新增mysql操作的支持
    2017.2.9  目录调整
    2017.3.2  新增ManagerServer例程
	2018.2.28 新增luaScript库
