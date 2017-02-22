/*
 * Copyright (c) 2012-2016 soymuchacho <guqi_282@126.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * > LIBSHARED  VERSION 		:		0.0.1 
 * > File Name					:		pyscript.h
 * > Author						:		soymuchacho
 * > Created Time				:		2017年02月13日 星期一 15时52分06秒
 * > brief						:		
 *
 * */

#ifndef SHARED_PYSCRIPT_H
#define SHARED_PYSCRIPT_H

#include <unistd.h>
#include <common/Log.h>
#include <common/MemoryPool.h>

namespace Shared
{

namespace PYSCRIPT
{

    template<typename T>
    void GetFuncParamStr(std::string & str, T && arg)
    {
        std::string strType = typeid(arg).name();
        if(strType.compare("PKc") == 0)
            str += "s"; 
        else if(strType.compare("b"))
        else
            str += "O";
    }

    template<typename T,typename... Args>
    void GetFuncParamStr(std::string & str, T && arg, Args&&... args)
    {
        GetFuncParamStr(str,forword<Args>(args)...)); 
    }

    // 返回值类
    class PyRet
    {
    public:
        PyRet(PyObject * obj){
            m_obj = obj;
        }
        ~PyRet(){
            Py_DECREF(m_obj);
        }
    public:
        string          GetString();
        int             GetInt();
        unsigned int    GetUInt();
        float           GetFloat();
        long            GetLong();
        long long       GetLongLong();
    private:
        PyObject * m_obj;
    };

    class pyfile
    {
    public:
        pyfile(){
        }
        ~pyfile(){
        }
    public:
        // 初始化...导入文件
        bool Initialize(char * filename){
        
            char file[256] = {0};
            // 去掉.py结尾
            file = strtok(filename,".");
            // 导入
            m_fp = PyImport_ImportModule(file);
            if(!m_fp)
            {
                LOGDEBUG("debug","import python file error!");
                return false;
            }
            // 解析字典
            m_pDict = PyModule_GetDict(m_fp);
            if(!m_pDict)
            {
                LOGDEBUG("debug","python module parse dict error!");
                return false;
            }
            return true;
        }

        template<typename... Args>
        PyRet * CallFunction(char * function,Args... args)
        {
            PyObject * pFunc = PyDict_GetItemString(pDict,function);
            if(!pFunc)
            {
                LOGDEBUG("debug","can't find %s func",function);
                return false;
            }
            PyObject * pRet = PyObject_CallFunction(pFunc,"",args...);
        }

        PyRet * ConstructClassInstance(char * className);
        PyRet * CallInstanceMethod(PyObject * classInstance,char * Method);
    protected:
        char        m_filename[256];                             /**< py文件名>*/
        PyObject *  m_fp;                                        /**< py文件操作句柄 >*/
        PyObject *  m_pDict;                                     /**< 字典模块 >*/
    };

    class pyscript
    {
    public:
        pyscript();
        ~pyscript();
    public:
        // 初始化Python环境,加载pyfile_path目录下的所有python文件
        bool Initialize(char * pyfile_path){
            if(pyfile_path == NULL)
            {
                LOGDEBUG("debug","initialize pyscript error : pyfile path is null!");
                return false; 
            }

            // 初始化python解释器环境
            Py_Initialize();
            if(!Py_IsInitialize())
            {
                LOGDEBUG("debug","initialize pyscript error : python解释器初始化error!");
                return false;
            }
            // 加入pypath
            PyRun_SimpleString("import sys");
            char append_path[280] = {0};
            snprintf(append_path,280,"sys.path.append('%s')",pyfile_path);
            PyRun_SimpleString(append_path);
            
            // 导入目录下所有的py文件
            DIR * dp;
            struct dirent * dirp;

            dp = opendir(pyfile_path);
            if(dp == NULL)
            {
                LOGDEBUG("debug","Initialize pyscript error :can't open path %s!",pyfile_path);
                return false;
            }

            while((dirp = readdir(dp)) != NULL)
            {
                // 循环该目录下的文件
                if(dirp->d_type == DT_BLK)
                {
                    // 文件导入..
                    LOGDEBUG("debug","import pyfile : %s ",dirp->d_name);
                    Import_PyFile(dirp->d_name);
                }
            }
            return true;
        }
        // 释放Python环境
        void Release(){
            Py_Finalize();
        }
    private:
        // 导入python脚本,filename不要.py结尾..
        bool ImportPyFile(char * filename){
            if(filename == NULL)
            {
                LOGDEBUG("debug","import python file error : filename is null");
                return false;
            }
            
            pyfile * pf = MM_NEW<pyfile>();
            if(pf == NULL)
            {
                LOGDEBUG("debug","alloc pyfile error!");
                return false;
            }

            if(pf->Initialize(filename) == false)
            {
                LOGDEBUG("debug","pyfile Initialize error!");
                MM_DELETE(pf);
                return false;
            }
            m_objectmap.insert(make_pair(filename,pf));
            return true;
        }
    protected:
        map<std::string,pyfile *> m_objectmap;            /**< 存放目录下所有的py文件 >*/
    };
}

}

#endif


