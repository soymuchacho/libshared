#pragma once
#pragma execution_character_set("utf-8")

#include <string>
#include <map>
#include "SeTableResBase.h"



//  自动生成表结构
struct TSLuaScriptTable : SeTableResBase
{
    unsigned int               uiScriptID                          ;   //  脚本ID   
    std::string                kName                               ;   //  文件名   
    std::string                kPath                               ;   //  路径   
};

class TiXmlElement;
class TSLuaScriptTableMgr
{
public:
    static TSLuaScriptTableMgr* Get();
    TSLuaScriptTableMgr();
    ~TSLuaScriptTableMgr();

    const TSLuaScriptTable* GetTSLuaScriptTable(unsigned int iTypeID);
    const std::map<unsigned int, TSLuaScriptTable*>& GetTSLuaScriptTableMap();
    TableResArray GetTSLuaScriptTableVec();

private:
    bool    Load();
    void    FillData(TSLuaScriptTable* row, TiXmlElement* element);

    std::map<unsigned int,TSLuaScriptTable*>      m_kTSLuaScriptTableMap;
    static TSLuaScriptTableMgr* m_pkTSLuaScriptTableMgr;
};
