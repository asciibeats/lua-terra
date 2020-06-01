#include "lterralib.h"
#include <terra.h>
#include <map>
#include <lua.hpp>

#define TERRA_LUAT "terra"
#define checksmap(L, index) *(SquareMap **)luaL_checkudata(L, index, TERRA_LUAT)

using namespace std;

static void smap_pushtiles(lua_State *L, SquareMap *smap)
{
  lua_createtable(L, smap->size * smap->size, 0);

  for (map<int, int>::iterator it = smap->tiles.begin(); it != smap->tiles.end(); it++) 
  {
    lua_pushinteger(L, it->second + 1);
    lua_rawseti(L, -2, it->first + 1);
  }
}

static void smap_pushtile(lua_State *L, SquareMap *smap, int position)
{
  lua_pushinteger(L, smap->generate(position - 1) + 1);
}

static int terra_new(lua_State *L)
{
  int seed = luaL_optinteger(L, 1, 7);
  int size = luaL_optinteger(L, 2, 40);
  int depth = luaL_optinteger(L, 3, 6);
  float frequency = luaL_optnumber(L, 4, 1.0f);
  int octaves = luaL_optinteger(L, 5, 2);
  float lacunarity = luaL_optnumber(L, 6, 0.5f);
  float persistence = luaL_optnumber(L, 7, 2.0f);

  SquareMap **smap = (SquareMap **)lua_newuserdata(L, sizeof(SquareMap*));
  *smap = new SquareMap(seed, size, depth, frequency, octaves, lacunarity, persistence);

  luaL_getmetatable(L, TERRA_LUAT);
  lua_setmetatable(L, -2);

  return 1;
}

//static int terra_gc(lua_State *L)
//{
//  SquareMap *smap = checksmap(L, 1);
//
//  return 0;
//}

static int terra_len(lua_State *L)
{
  SquareMap *smap = checksmap(L, 1);
  lua_pushinteger(L, smap->size * smap->size);

  return 1;
}

static int terra_size(lua_State *L)
{
  SquareMap *smap = checksmap(L, 1);
  lua_pushinteger(L, smap->size);

  return 1;
}

static int terra_tiles(lua_State *L)
{
  SquareMap *smap = checksmap(L, 1);
  smap_pushtiles(L, smap);

  return 1;
}

static int terra_generate(lua_State *L)
{
  SquareMap *smap = checksmap(L, 1);
  lua_Integer position = lua_tointeger(L, 2);

  if (position > 0)
  {
    smap_pushtile(L, smap, position);
  }
  else
  {
    smap->generate();
    smap_pushtiles(L, smap);
  }

  return 1;
}

static const struct luaL_Reg terra_func [] = {
  {"new", terra_new},
  {NULL, NULL}
};

static const struct luaL_Reg terra_meta [] = {
  //{"__gc", terra_gc},
  {"__len", terra_len},
  {"size", terra_size},
  {"tiles", terra_tiles},
  {"generate", terra_generate},
  {NULL, NULL}
};

int luaopen_terra(lua_State *L)
{
  luaL_newmetatable(L, TERRA_LUAT);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, terra_meta, 0);
  luaL_newlib(L, terra_func);

  return 1;
}
