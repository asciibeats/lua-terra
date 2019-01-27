#ifndef lterralib_h
#define lterralib_h

#include <lua.hpp>

#define TERRA_LIBNAME "terra"

extern "C" int luaopen_terra(lua_State *L);

#endif
