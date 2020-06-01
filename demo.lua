local terra = require('terra')

local map = terra.new()
local size = map:size()
local tiles = map:generate()

local terrains = {'  ', '..', '~~', '++', 'xx', '##'}

for y = 0, size - 1 do
	for x = 0, size - 1 do
		io.write(terrains[tiles[y * size + x + 1]])
	end
	io.write('\n')
end
