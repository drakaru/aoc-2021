// day11.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <numeric>

using namespace std::string_literals;

struct Octopus
{
	uint8_t energy;
	uint16_t flashed;

	bool incr(uint16_t tick)
	{
		if (tick > flashed)
		{
			energy++;
			if (energy > 9)
			{
				flashed = tick;
				energy = 0;
				return true;
			}
		}
		return false;
	}
};

size_t get_idx(size_t x, size_t y)
{
	return y * 10 + x;
}

bool try_incr(std::array<Octopus, 100>& octopi, uint16_t tick, size_t x, size_t y)
{
	if (x < 10 && y < 10)
	{
		return octopi[get_idx(x, y)].incr(tick);
	}
	return false;
}

void flash(std::array<Octopus, 100>& octopi, uint64_t& flashes, uint16_t tick, size_t x, size_t y)
{
	if (try_incr(octopi, tick, x - 1, y - 1)) { flashes++; flash(octopi, flashes, tick, x - 1, y - 1); }
	if (try_incr(octopi, tick, x - 1, y)) { flashes++; flash(octopi, flashes, tick, x - 1, y); }
	if (try_incr(octopi, tick, x - 1, y + 1)) { flashes++; flash(octopi, flashes, tick, x - 1, y + 1); }
	if (try_incr(octopi, tick, x, y - 1)) { flashes++; flash(octopi, flashes, tick, x, y - 1); }
	if (try_incr(octopi, tick, x, y + 1)) { flashes++; flash(octopi, flashes, tick, x, y + 1); }
	if (try_incr(octopi, tick, x + 1, y - 1)) { flashes++; flash(octopi, flashes, tick, x + 1, y - 1); }
	if (try_incr(octopi, tick, x + 1, y)) { flashes++; flash(octopi, flashes, tick, x + 1, y); }
	if (try_incr(octopi, tick, x + 1, y + 1)) { flashes++; flash(octopi, flashes, tick, x + 1, y + 1); }
}

int main()
{
	std::array<Octopus, 100> octopi{};
	uint64_t flashes = 0;
	uint16_t tick = 0;
	uint64_t tick_flashes = 0;

	auto f = std::ifstream("day11.txt");

	for (auto& octopus : octopi)
	{
		f >> octopus.energy;
		octopus.energy -= '0';
	}

	while (tick_flashes != 100)
	{
		tick_flashes = 0;
		tick++;

		for (size_t y = 0; y < 10; ++y)
		{
			for (size_t x = 0; x < 10; ++x)
			{
				bool flashed = octopi[get_idx(x, y)].incr(tick);
				if (flashed)
				{
					tick_flashes++;
					flash(octopi, tick_flashes, tick, x, y);
				}
			}
		}

		flashes += tick_flashes;

		if (tick == 100)
		{
			std::cout << "part1 = " << flashes << "\n";
		}

		if (tick_flashes == 100)
		{
			std::cout << "part2 = " << tick << "\n";
			break;
		}
	}
}
