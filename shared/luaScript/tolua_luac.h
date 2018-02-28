/*
** Lua binding: luac
** Generated automatically by tolua++-1.0.92 on 02/27/18 13:36:43.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_luac_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_LuaC__CLuaStringList (lua_State* tolua_S)
{
 LuaC::CLuaStringList* self = (LuaC::CLuaStringList*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LuaC__CLuaIntList (lua_State* tolua_S)
{
 LuaC::CLuaIntList* self = (LuaC::CLuaIntList*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_LuaC__CLuaInt64 (lua_State* tolua_S)
{
 LuaC::CLuaInt64* self = (LuaC::CLuaInt64*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"LuaC::CLuaStringList");
 tolua_usertype(tolua_S,"LuaC::CLuaIntList");
 tolua_usertype(tolua_S,"LuaC::CLuaInt64");
}

/* method: new of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new00
static int tolua_luac_LuaC_CLuaInt64_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new00_local
static int tolua_luac_LuaC_CLuaInt64_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new01
static int tolua_luac_LuaC_CLuaInt64_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new01_local
static int tolua_luac_LuaC_CLuaInt64_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new02
static int tolua_luac_LuaC_CLuaInt64_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new02_local
static int tolua_luac_LuaC_CLuaInt64_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new03
static int tolua_luac_LuaC_CLuaInt64_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(*a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new03_local
static int tolua_luac_LuaC_CLuaInt64_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(*a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new04
static int tolua_luac_LuaC_CLuaInt64_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string a_data = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
   tolua_pushcppstring(tolua_S,(const char*)a_data);
  }
 }
 return 2;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_new04_local
static int tolua_luac_LuaC_CLuaInt64_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string a_data = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   LuaC::CLuaInt64* tolua_ret = (LuaC::CLuaInt64*)  Mtolua_new((LuaC::CLuaInt64)(a_data));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)a_data);
  }
 }
 return 2;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_delete00
static int tolua_luac_LuaC_CLuaInt64_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaInt64* self = (LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__add00
static int tolua_luac_LuaC_CLuaInt64__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator+(*a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__sub00
static int tolua_luac_LuaC_CLuaInt64__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator-(*a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__mul00
static int tolua_luac_LuaC_CLuaInt64__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator*(*a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__div00
static int tolua_luac_LuaC_CLuaInt64__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator/(*a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__add01
static int tolua_luac_LuaC_CLuaInt64__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator+(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__sub01
static int tolua_luac_LuaC_CLuaInt64__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator-(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__mul01
static int tolua_luac_LuaC_CLuaInt64__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator*(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__div01
static int tolua_luac_LuaC_CLuaInt64__div01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator/(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__div00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__add02
static int tolua_luac_LuaC_CLuaInt64__add02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator+(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__add01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__sub02
static int tolua_luac_LuaC_CLuaInt64__sub02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator-(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__sub01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__mul02
static int tolua_luac_LuaC_CLuaInt64__mul02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator*(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__mul01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__div02
static int tolua_luac_LuaC_CLuaInt64__div02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   LuaC::CLuaInt64 tolua_ret = (LuaC::CLuaInt64)  self->operator/(a_data);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LuaC::CLuaInt64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaC::CLuaInt64));
     tolua_pushusertype(tolua_S,tolua_obj,"LuaC::CLuaInt64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__div01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__lt00
static int tolua_luac_LuaC_CLuaInt64__lt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<(*a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.lt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__lt01
static int tolua_luac_LuaC_CLuaInt64__lt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<(a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__lt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__lt02
static int tolua_luac_LuaC_CLuaInt64__lt02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<(a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__lt01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator<= of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__le00
static int tolua_luac_LuaC_CLuaInt64__le00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<=(*a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.le'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator<= of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__le01
static int tolua_luac_LuaC_CLuaInt64__le01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<=(a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__le00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator<= of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__le02
static int tolua_luac_LuaC_CLuaInt64__le02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<=(a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__le01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__eq00
static int tolua_luac_LuaC_CLuaInt64__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__eq01
static int tolua_luac_LuaC_CLuaInt64__eq01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__eq00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64__eq02
static int tolua_luac_LuaC_CLuaInt64__eq02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(a_data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64__eq01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setData of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_setData00
static int tolua_luac_LuaC_CLuaInt64_setData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaInt64* self = (LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  int a_data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setData'", NULL);
#endif
  {
   self->setData(a_data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setData of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_setData01
static int tolua_luac_LuaC_CLuaInt64_setData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  LuaC::CLuaInt64* self = (LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  float a_data = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setData'", NULL);
#endif
  {
   self->setData(a_data);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_setData00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setData of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_setData02
static int tolua_luac_LuaC_CLuaInt64_setData02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaC::CLuaInt64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  LuaC::CLuaInt64* self = (LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const LuaC::CLuaInt64* a_data = ((const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setData'", NULL);
#endif
  {
   self->setData(*a_data);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_setData01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setData of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_setData03
static int tolua_luac_LuaC_CLuaInt64_setData03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  LuaC::CLuaInt64* self = (LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  const std::string a_data = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setData'", NULL);
#endif
  {
   self->setData(a_data);
   tolua_pushcppstring(tolua_S,(const char*)a_data);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_setData02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: toString of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_toString00
static int tolua_luac_LuaC_CLuaInt64_toString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->toString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toString of class  LuaC::CLuaInt64 */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaInt64_toString01
static int tolua_luac_LuaC_CLuaInt64_toString01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaInt64",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const LuaC::CLuaInt64* self = (const LuaC::CLuaInt64*)  tolua_tousertype(tolua_S,1,0);
  char a_type = ((char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->toString(a_type);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaInt64_toString00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_new00
static int tolua_luac_LuaC_CLuaIntList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaC::CLuaIntList* tolua_ret = (LuaC::CLuaIntList*)  Mtolua_new((LuaC::CLuaIntList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaIntList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_new00_local
static int tolua_luac_LuaC_CLuaIntList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaC::CLuaIntList* tolua_ret = (LuaC::CLuaIntList*)  Mtolua_new((LuaC::CLuaIntList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaIntList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_new01
static int tolua_luac_LuaC_CLuaIntList_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int a_size = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaIntList* tolua_ret = (LuaC::CLuaIntList*)  Mtolua_new((LuaC::CLuaIntList)(a_size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaIntList");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaIntList_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_new01_local
static int tolua_luac_LuaC_CLuaIntList_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int a_size = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaIntList* tolua_ret = (LuaC::CLuaIntList*)  Mtolua_new((LuaC::CLuaIntList)(a_size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaIntList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaIntList_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_delete00
static int tolua_luac_LuaC_CLuaIntList_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaIntList* self = (LuaC::CLuaIntList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_clear00
static int tolua_luac_LuaC_CLuaIntList_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaIntList* self = (LuaC::CLuaIntList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_addItem00
static int tolua_luac_LuaC_CLuaIntList_addItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaIntList* self = (LuaC::CLuaIntList*)  tolua_tousertype(tolua_S,1,0);
  const int a_item = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   self->addItem(a_item);
   tolua_pushnumber(tolua_S,(lua_Number)a_item);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList_getSize00
static int tolua_luac_LuaC_CLuaIntList_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaIntList* self = (const LuaC::CLuaIntList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  LuaC::CLuaIntList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaIntList__geti00
static int tolua_luac_LuaC_CLuaIntList__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaIntList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaIntList* self = (LuaC::CLuaIntList*)  tolua_tousertype(tolua_S,1,0);
  int a_index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   int tolua_ret = (int)  self->operator[](a_index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_new00
static int tolua_luac_LuaC_CLuaStringList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaC::CLuaStringList* tolua_ret = (LuaC::CLuaStringList*)  Mtolua_new((LuaC::CLuaStringList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaStringList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_new00_local
static int tolua_luac_LuaC_CLuaStringList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaC::CLuaStringList* tolua_ret = (LuaC::CLuaStringList*)  Mtolua_new((LuaC::CLuaStringList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaStringList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_new01
static int tolua_luac_LuaC_CLuaStringList_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int a_size = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaStringList* tolua_ret = (LuaC::CLuaStringList*)  Mtolua_new((LuaC::CLuaStringList)(a_size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaStringList");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaStringList_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_new01_local
static int tolua_luac_LuaC_CLuaStringList_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int a_size = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LuaC::CLuaStringList* tolua_ret = (LuaC::CLuaStringList*)  Mtolua_new((LuaC::CLuaStringList)(a_size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaC::CLuaStringList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaStringList_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_delete00
static int tolua_luac_LuaC_CLuaStringList_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaStringList* self = (LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_clear00
static int tolua_luac_LuaC_CLuaStringList_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaStringList* self = (LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_addItem00
static int tolua_luac_LuaC_CLuaStringList_addItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaStringList* self = (LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
  const std::string a_item = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   self->addItem(a_item);
   tolua_pushcppstring(tolua_S,(const char*)a_item);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList_getSize00
static int tolua_luac_LuaC_CLuaStringList_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaStringList* self = (const LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList__geti00
static int tolua_luac_LuaC_CLuaStringList__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaC::CLuaStringList* self = (const LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
  int a_index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->operator[](a_index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList__seti00
static int tolua_luac_LuaC_CLuaStringList__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaC::CLuaStringList* self = (LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
  int a_index = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string tolua_value = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](a_index) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  LuaC::CLuaStringList */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_CLuaStringList__geti01
static int tolua_luac_LuaC_CLuaStringList__geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaC::CLuaStringList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  LuaC::CLuaStringList* self = (LuaC::CLuaStringList*)  tolua_tousertype(tolua_S,1,0);
  int a_index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->operator[](a_index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luac_LuaC_CLuaStringList__geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LuaC::luaLogDebug */
#ifndef TOLUA_DISABLE_tolua_luac_LuaC_luaLogDebug00
static int tolua_luac_LuaC_luaLogDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string strText = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   LuaC::luaLogDebug(strText);
   tolua_pushcppstring(tolua_S,(const char*)strText);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'luaLogDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_luac_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"LuaC",0);
  tolua_beginmodule(tolua_S,"LuaC");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CLuaInt64","LuaC::CLuaInt64","",tolua_collect_LuaC__CLuaInt64);
   #else
   tolua_cclass(tolua_S,"CLuaInt64","LuaC::CLuaInt64","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CLuaInt64");
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaInt64_new00);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaInt64_new00_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaInt64_new00_local);
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaInt64_new01);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaInt64_new01_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaInt64_new01_local);
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaInt64_new02);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaInt64_new02_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaInt64_new02_local);
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaInt64_new03);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaInt64_new03_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaInt64_new03_local);
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaInt64_new04);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaInt64_new04_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaInt64_new04_local);
    tolua_function(tolua_S,"delete",tolua_luac_LuaC_CLuaInt64_delete00);
    tolua_function(tolua_S,".add",tolua_luac_LuaC_CLuaInt64__add00);
    tolua_function(tolua_S,".sub",tolua_luac_LuaC_CLuaInt64__sub00);
    tolua_function(tolua_S,".mul",tolua_luac_LuaC_CLuaInt64__mul00);
    tolua_function(tolua_S,".div",tolua_luac_LuaC_CLuaInt64__div00);
    tolua_function(tolua_S,".add",tolua_luac_LuaC_CLuaInt64__add01);
    tolua_function(tolua_S,".sub",tolua_luac_LuaC_CLuaInt64__sub01);
    tolua_function(tolua_S,".mul",tolua_luac_LuaC_CLuaInt64__mul01);
    tolua_function(tolua_S,".div",tolua_luac_LuaC_CLuaInt64__div01);
    tolua_function(tolua_S,".add",tolua_luac_LuaC_CLuaInt64__add02);
    tolua_function(tolua_S,".sub",tolua_luac_LuaC_CLuaInt64__sub02);
    tolua_function(tolua_S,".mul",tolua_luac_LuaC_CLuaInt64__mul02);
    tolua_function(tolua_S,".div",tolua_luac_LuaC_CLuaInt64__div02);
    tolua_function(tolua_S,".lt",tolua_luac_LuaC_CLuaInt64__lt00);
    tolua_function(tolua_S,".lt",tolua_luac_LuaC_CLuaInt64__lt01);
    tolua_function(tolua_S,".lt",tolua_luac_LuaC_CLuaInt64__lt02);
    tolua_function(tolua_S,".le",tolua_luac_LuaC_CLuaInt64__le00);
    tolua_function(tolua_S,".le",tolua_luac_LuaC_CLuaInt64__le01);
    tolua_function(tolua_S,".le",tolua_luac_LuaC_CLuaInt64__le02);
    tolua_function(tolua_S,".eq",tolua_luac_LuaC_CLuaInt64__eq00);
    tolua_function(tolua_S,".eq",tolua_luac_LuaC_CLuaInt64__eq01);
    tolua_function(tolua_S,".eq",tolua_luac_LuaC_CLuaInt64__eq02);
    tolua_function(tolua_S,"setData",tolua_luac_LuaC_CLuaInt64_setData00);
    tolua_function(tolua_S,"setData",tolua_luac_LuaC_CLuaInt64_setData01);
    tolua_function(tolua_S,"setData",tolua_luac_LuaC_CLuaInt64_setData02);
    tolua_function(tolua_S,"setData",tolua_luac_LuaC_CLuaInt64_setData03);
    tolua_function(tolua_S,"toString",tolua_luac_LuaC_CLuaInt64_toString00);
    tolua_function(tolua_S,"toString",tolua_luac_LuaC_CLuaInt64_toString01);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CLuaIntList","LuaC::CLuaIntList","",tolua_collect_LuaC__CLuaIntList);
   #else
   tolua_cclass(tolua_S,"CLuaIntList","LuaC::CLuaIntList","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CLuaIntList");
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaIntList_new00);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaIntList_new00_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaIntList_new00_local);
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaIntList_new01);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaIntList_new01_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaIntList_new01_local);
    tolua_function(tolua_S,"delete",tolua_luac_LuaC_CLuaIntList_delete00);
    tolua_function(tolua_S,"clear",tolua_luac_LuaC_CLuaIntList_clear00);
    tolua_function(tolua_S,"addItem",tolua_luac_LuaC_CLuaIntList_addItem00);
    tolua_function(tolua_S,"getSize",tolua_luac_LuaC_CLuaIntList_getSize00);
    tolua_function(tolua_S,".geti",tolua_luac_LuaC_CLuaIntList__geti00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CLuaStringList","LuaC::CLuaStringList","",tolua_collect_LuaC__CLuaStringList);
   #else
   tolua_cclass(tolua_S,"CLuaStringList","LuaC::CLuaStringList","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CLuaStringList");
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaStringList_new00);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaStringList_new00_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaStringList_new00_local);
    tolua_function(tolua_S,"new",tolua_luac_LuaC_CLuaStringList_new01);
    tolua_function(tolua_S,"new_local",tolua_luac_LuaC_CLuaStringList_new01_local);
    tolua_function(tolua_S,".call",tolua_luac_LuaC_CLuaStringList_new01_local);
    tolua_function(tolua_S,"delete",tolua_luac_LuaC_CLuaStringList_delete00);
    tolua_function(tolua_S,"clear",tolua_luac_LuaC_CLuaStringList_clear00);
    tolua_function(tolua_S,"addItem",tolua_luac_LuaC_CLuaStringList_addItem00);
    tolua_function(tolua_S,"getSize",tolua_luac_LuaC_CLuaStringList_getSize00);
    tolua_function(tolua_S,".geti",tolua_luac_LuaC_CLuaStringList__geti00);
    tolua_function(tolua_S,".seti",tolua_luac_LuaC_CLuaStringList__seti00);
    tolua_function(tolua_S,".geti",tolua_luac_LuaC_CLuaStringList__geti01);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"luaLogDebug",tolua_luac_LuaC_luaLogDebug00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_luac (lua_State* tolua_S) {
 return tolua_luac_open(tolua_S);
};
#endif

