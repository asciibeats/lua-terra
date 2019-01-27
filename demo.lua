local terra = require('terra')
local map = terra.gensquare(7, 4, 0.8, 3, 0.6, 0.3, 0.5, 0.5, 0.5)
local terrains = {'   ', '###'}

for y = 0, map.width - 1 do
	for x = 0, map.width - 1 do
		io.write(terrains[map.tiles[y * map.width + x + 1]])
	end
	io.write('\n')
end
