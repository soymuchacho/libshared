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

#include <python2.7/Python.h>
#include <unistd.h>
#include <common/Log.h>
#include <common/MemoryPool.h>
#include <pyscript/py_config.h>

namespace Shared
{

namespace PYSCRIPT
{

    /*
     * typeid.name 返回值 
     * bool : b
     * char : c
     * signed char : a
     * unsigned char : h
     * (signed) short (int) : s
     * unsigned short (int) : t
     * (signed)(int): i
     * unsigned int : j
     * long : l
     * unsigned long : m
     * long long : x
     * unsigned long long : y
     * float : f
     * double : d
     * long double : e
     */
    template<typename T>
    void GetFuncParamStr(std::string & str, T && arg)
    {
        std::string strType = typeid(arg).name();
        str += GetTypeStr(strType);
    }

    template<typename T,typename... Args>
    void GetFuncParamStr(std::string & str, T && arg, Args&&... args)
    {
        str += typeid(arg).name();
        GetFuncParamStr(str,std::forward<Args>(args)...); 
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
        PyObject *          GetPyObject() { return m_obj; }
        string              GetString() { return PyString_AsString(m_obj); }
        int                 GetInt() { return PyInt_AsLong(m_obj); }
        unsigned int        GetUInt() { return PyInt_AsUnsignedLongMask(m_obj); }
        float               GetFloat() { return PyFloat_AsDouble(m_obj); }
        double              GetDouble() { return PyFloat_AsDouble(m_obj); }
        long                GetLong() { return PyInt_AsLong(m_obj); }
        Py_ssize_t          GetPyssize_t() { return PyInt_AsUnsignedLongLongMask(m_obj); }
        unsigned long long  GetULongLong() { return PyInt_AsUnsignedLongLongMask(m_obj); }
    private:
        PyObject * m_obj;
    };

    class pyfile
    {
    public:
        pyfile(){
        }
        ~pyfile(){
            Py_DECREF(m_fp);
            Py_DECREF(m_pDict);
        }
    public:
        // 初始化...导入文件
        bool Initialize(char * file){
        
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

            // 打印..
            if(!PyDict_Check(m_pDict))
                return false;

            PyObject *k,*keys;
            keys = PyDict_Keys(m_pDict);
            for(int i = 0; i < PyList_GET_SIZE(keys);i++)
            {
                k = PyList_GET_ITEM(keys,i);
                char * c_name = PyString_AsString(k);
                LOGDEBUG("debug","attr : %s",c_name);
            }
            return true;
        }

        // 此处返回的PyRet需要自己手动释放！调用MM_DELETE来释放！
        template<typename... Args>
        PyRet * CallFunction(const char * function,Args... args)
        {
            PyObject * pFunc = PyDict_GetItemString(m_pDict,function);
            if(!pFunc)
            {
                LOGDEBUG("debug","can't find %s func",function);
                return NULL;
            }

            string str;
            GetFuncParamStr(str,args...);
           
            LOGDEBUG("debug","function %s param : %s",function,str.c_str());

            PyObject * pRet = PyObject_CallFunction(pFunc,(char *)str.c_str(),args...);
        
            if(pRet == NULL)
                return NULL;
            
            PyRet * ret = MM_NEW<PyRet>(pRet);
            if(ret == NULL)
            {
                Py_DECREF(pRet);
                LOGDEBUG("debug","CallFunction返回值分配空间失败！");
                return NULL;
            }
            return ret;
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
        pyscript() {
        
        }
        ~pyscript(){
            
        }
    public:
        // 初始化Python环境,加载pyfile_path目录下的所有python文件
        bool Initialize(const char * pyfile_path){
            if(pyfile_path == NULL)
            {
                LOGDEBUG("debug","initialize pyscript error : pyfile path is null!");
                return false; 
            }
            LOGDEBUG("debug","pyscript begin initialize");
            // 初始化python解释器环境
            Py_Initialize();
            if(!Py_IsInitialized())
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

            LOGDEBUG("debug","pyscript initialize open dir %s",pyfile_path);
            while((dirp = readdir(dp)) != NULL)
            {
                LOGDEBUG("debug","[%s]:[%d]",dirp->d_name,dirp->d_type);
                // 循环该目录下的文件
                if(dirp->d_type != DT_DIR)
                {
                    // 文件导入..
                    LOGDEBUG("debug","import pyfile : %s ",dirp->d_name);
                  
                    // 判断是不是.py文件
                    if(strstr(dirp->d_name,".py") != NULL && strstr(dirp->d_name,".pyc") == NULL)
                    {
                        // 去掉.py结尾
                        char * file = strtok(dirp->d_name,".");

                        ImportPyFile(file);
                    }
                }
            }
            LOGDEBUG("debug","pyscript end initialize");
            return true;
        }

        // 此处返回的PyRet需要自己手动释放！调用MM_DELETE来释放！
        template<typename... Args>
        PyRet * CallFunction(const char * function,Args... args)
        {
            map<std::string,pyfile *>::iterator itr;
            for(itr = m_objectmap.begin(); itr != m_objectmap.end();itr++)
            {
                pyfile * pf = itr->second;
                if(pf)
                {
                    PyRet * pr = pf->CallFunction(function,forward<Args>(args)...);
                    if(pr == NULL)
                        continue;
                    else
                        return pr;
                }
            }
            return NULL;
        }
        // 释放Python环境
        void Release(){
            // 卸载掉加载的文件
            map<std::string,pyfile *>::iterator itr;
            for(itr = m_objectmap.begin(); itr != m_objectmap.end();itr++)
            {
                pyfile * pf = itr->second;
                if(pf)
                {
                    MM_DELETE(pf);
                }
            }
            m_objectmap.clear();

            // 关闭Python解释器
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

            map<std::string,pyfile *>::iterator itr;
            itr = m_objectmap.find(filename);
            if(itr != m_objectmap.end())
            {
                LOGDEBUG("debug","python 模块%s已经存在，不需要继续加载！",filename);
                return true;
            }

            if(pf->Initialize(filename) == false)
            {
                LOGDEBUG("debug","pyfile Initialize error!");
                MM_DELETE(pf);
                return false;
            }
            LOGDEBUG("debug","pyfile initialize %s",filename);
            m_objectmap.insert(make_pair(filename,pf));
            return true;
        }
    protected:
        map<std::string,pyfile *> m_objectmap;            /**< 存放目录下所有的py文件 >*/
    };
}

}

#endif


