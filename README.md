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
    |—— examples                                    // 使用libshared的简单服务器例程
    |    |—— daytime                                // 时间核对服务器及客户端
    |    |—— echo                                   // echo服务器
    |    |—— time-task                              // 计时事件的使用例程
    |—— shared                                      // libshared的主体
    |    |—— base                                   // 基础库
    |    |—— network                                // 网络相关的封装
    |    |—— utility                                // 实用库
    |    |—— include                                // 头文件
    |—— sql											// 对mysql的支持
    |—— lua											// c++调用lua及lua调用c++接口支持
    |—— python										// c++调用python及python调用c++接口支持

Class 
----------------------------------

Building & install
----------------------------------

    $ mkdir build
    $ cd libshared/
    $ make clean 
    $ make 
    $ make install 

	// 请先自行安装Mysql,然后再进行编译
	// 增加mysql支持
	$ make EnableMYSQL=true

Wishes Extension
------------------------------------
	2016.5.1
	* suport mysql
    * suport python 
    * suport lua 

Change Log
----------------------------------

    2016.9.22 新增mysql操作的支持
    2017.2.9  目录调整
