#include "lterralib.h"
#include <terra.h>
#include <map>
#include <lua.hpp>

using namespace std;

static int terra_gensquare(lua_State *L)
{
  int seed = luaL_optinteger(L, 1, 7);
  int size = luaL_optinteger(L, 2, 32);
  int depth = luaL_optinteger(L, 3, 4);
  float frequency = luaL_optnumber(L, 4, 1.0f);
  int octaves = luaL_optinteger(L, 5, 2);
  float lacunarity = luaL_optnumber(L, 6, 0.5f);
  float persistence = luaL_optnumber(L, 7, 2.0f);
  float erosion = luaL_optnumber(L, 8, 0.5f);

  SquareMap smap;
  smap.generate(seed, size, depth, frequency, octaves, lacunarity, persistence, erosion);
  lua_createtable(L, 0, 3);
  lua_pushliteral(L, "seed");
  lua_pushinteger(L, seed);
  lua_rawset(L, -3);
  lua_pushliteral(L, "size");
  lua_pushinteger(L, size);
  lua_rawset(L, -3);
  lua_pushliteral(L, "depth");
  lua_pushinteger(L, depth);
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
