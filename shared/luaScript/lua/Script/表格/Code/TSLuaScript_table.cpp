#include "TSLuaScript_table.hpp"
#include "tinyxml.h"
#include "EeFileMemory.h"
#include "EeFilePackage.h"

TSLuaScriptTableMgr* TSLuaScriptTableMgr::m_pkTSLuaScriptTableMgr = NULL;
TSLuaScriptTableMgr* TSLuaScriptTableMgr::Get()
{
    if(m_pkTSLuaScriptTableMgr == NULL)
    {
        m_pkTSLuaScriptTableMgr = new TSLuaScriptTableMgr();
    }
    return m_pkTSLuaScriptTableMgr;
}


const std::map<unsigned int, TSLuaScriptTable*>& TSLuaScriptTableMgr::GetTSLuaScriptTableMap()
{
    return m_kTSLuaScriptTableMap;
}

TableResArray TSLuaScriptTableMgr::GetTSLuaScriptTableVec()
{
    TableResArray kRecVec;
    for (std::map<unsigned int, TSLuaScriptTable*>::iterator iMapItr = m_kTSLuaScriptTableMap.begin(); iMapItr != m_kTSLuaScriptTableMap.end(); ++iMapItr)
    {
        kRecVec.pushBack(iMapItr->second);
    }

    return kRecVec;
}

const TSLuaScriptTable* TSLuaScriptTableMgr::GetTSLuaScriptTable(unsigned int iTypeID)
{
    std::map<unsigned int, TSLuaScriptTable*>::iterator iter = m_kTSLuaScriptTableMap.find(iTypeID);
    if(iter != m_kTSLuaScriptTableMap.end())
    {
        return iter->second;
    }
    return NULL;
}

TSLuaScriptTableMgr::TSLuaScriptTableMgr()
{
    Load();
}

TSLuaScriptTableMgr::~TSLuaScriptTableMgr()
{
    m_kTSLuaScriptTableMap.clear();
}

bool TSLuaScriptTableMgr::Load()
{
    std::string path = "Data/Table/TSLuaScript.xml";
    FileMemory kMemory;
    if(!FileLoader::LoadTableFile(path.c_str(),kMemory))
    {
        return false;
    }

    TiXmlDocument doc;
    doc.Parse(kMemory.GetData());
    if (doc.Error())
    {
        std::string err = path + "   " + std::string(doc.ErrorDesc());
        // throw std::exception(err.c_str());
        return false;
    }

    TiXmlElement* root = doc.FirstChildElement("root");
    if (root == 0)
    {
        // throw std::exception("root is null!");
        return false;
    }

    TiXmlElement* element = root->FirstChildElement("content");
    while (element != 0)
    {
        TSLuaScriptTable * row = new TSLuaScriptTable();
        FillData(row, element);
        element = element->NextSiblingElement();
    }

    return true;
}

void TSLuaScriptTableMgr::FillData(TSLuaScriptTable* row, TiXmlElement* element)
{
    int int_value = 0;
    std::string str_value = "";

    element->Attribute("ScriptID", &int_value);
    row->uiScriptID = (unsigned int)int_value;
    str_value = element->Attribute("Name");
    row->kName = str_value;
    str_value = element->Attribute("Path");
    row->kPath = str_value;

    m_kTSLuaScriptTableMap[row->uiScriptID] = row;
}
