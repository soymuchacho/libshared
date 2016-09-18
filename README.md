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
    |—— build                                       // 
    |—— examples                                    // some examples whth use libshared
    |    |—— daytime                                // day time server and client
    |    |—— echo                                   // echo server
    |    |—— time-task                              // time task example
    |—— shared                                      // libshared main directory
    |    |—— base                                   // base
    |    |—— network                                // network headfile
    |    |—— utility                                // utility headfile
    |    |—— include                                // include   

Building & install
---------------

    $ mkdir build
    $ cd libshared/
    $ make clean 
    $ make 
    $ make install 

Change Log
------------------


