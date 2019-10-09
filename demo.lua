local terra = require('terra')
local map = terra.gensquare(7, 40, 6)
local terrains = {'  ', '..', '~~', '++', 'xx', '##'}

for y = 0, map.size - 1 do
	for x = 0, map.size - 1 do
		io.write(terrains[map.tiles[y * map.size + x + 1] + 1])
	end
	io.write('\n')
end
