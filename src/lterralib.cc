#include "lterralib.h"
#include <terra.h>
#include <map>
#include <lua.hpp>

using namespace std;

static int terra_gensquare(lua_State *L)
{
  int seed = luaL_checkinteger(L, 1);
  int size = luaL_checkinteger(L, 2);
  float frequency = luaL_checknumber(L, 3);
  int octaves = luaL_checkinteger(L, 4);
  float lacunarity = luaL_checknumber(L, 5);
  float persistence = luaL_checknumber(L, 6);
  float erosion = luaL_checknumber(L, 7);
  float water = luaL_checknumber(L, 8);
  float heat = luaL_checknumber(L, 9);

  SquareMap smap;
  smap.generate(seed, size, frequency, octaves, lacunarity, persistence, erosion, water, heat);
  lua_createtable(L, 0, 3);
  lua_pushliteral(L, "size");
  lua_pushinteger(L, smap.size);
  lua_rawset(L, -3);
  lua_pushliteral(L, "width");
  lua_pushinteger(L, smap.width);
  lua_rawset(L, -3);
  lua_pushliteral(L, "tiles");
  lua_createtable(L, 0, smap.tiles.size());

  for (map<int, int>::iterator it = smap.tiles.begin(); it != smap.tiles.end(); it++) 
  {
    lua_pushinteger(L, it->second);
    lua_rawseti(L, -2, it->first + 1);
  }

  lua_rawset(L, -3);
  return 1;
}

static const struct luaL_Reg terra_f [] = {
  {"gensquare", terra_gensquare},
  {NULL, NULL}
};

int luaopen_terra(lua_State *L)
{
  luaL_newlib(L, terra_f);
  return 1;
}
