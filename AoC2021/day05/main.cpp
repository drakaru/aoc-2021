// day05.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std::string_literals;

auto hash(auto x, auto y)
{
	return 1000 * x + y;
}

void add_point(auto& points, auto x, auto y)
{
	auto ph = hash(x, y);
	if (points.contains(ph))
	{
		points[ph] = points[ph] + 1;
	}
	else
	{
		points[ph] = 1;
	}
}

void parse_line(std::string line, auto& x1, auto& y1, auto& x2, auto& y2)
{
	auto si = line.find('-');
	line[si] = ',';
	line[si + 1] = ' ';
	std::erase_if(line, [](auto c) { return c == ' '; });
	std::transform(line.begin(), line.end(), line.begin(), [](auto i) { return i == ',' ? ' ' : i; });
	std::stringstream ls(line);
	
	ls >> x1 >> y1 >> x2 >> y2;
}

void part1()
{
	auto f = std::ifstream("day05.txt");
	std::unordered_map<uint64_t, uint64_t> points;

	std::string line;
	while (std::getline(f, line))
	{
		uint64_t x1, y1, x2, y2;
		parse_line(line, x1, y1, x2, y2);

		if (x1 == x2)
		{
			uint64_t sy = y1 > y2 ? y2 : y1;
			uint64_t ey = y1 > y2 ? y1 : y2;
			for (auto cy = sy; cy <= ey; ++cy)
			{
				add_point(points, x1, cy);
			}
		}
		else if (y1 == y2)
		{
			uint64_t sx = x1 > x2 ? x2 : x1;
			uint64_t ex = x1 > x2 ? x1 : x2;
			for (auto cx = sx; cx <= ex; ++cx)
			{
				add_point(points, cx, y1);
			}
		}
	}

	uint64_t danger_points = 0;
	for (auto& thing : points)
	{
		if (thing.second >= 2) 
		{
			danger_points++;
		}
	}

	std::cout << "part1 = " << danger_points << "\n";
}

void part2()
{
	auto f = std::ifstream("day05.txt");
	std::unordered_map<uint64_t, uint64_t> points;

	std::string line;
	while (std::getline(f, line))
	{
		uint64_t x1, y1, x2, y2;
		parse_line(line, x1, y1, x2, y2);

		if (x1 == x2)
		{
			uint64_t sy = y1 > y2 ? y2 : y1;
			uint64_t ey = y1 > y2 ? y1 : y2;
			for (auto cy = sy; cy <= ey; ++cy)
			{
				add_point(points, x1, cy);
			}
		}
		else if (y1 == y2)
		{
			uint64_t sx = x1 > x2 ? x2 : x1;
			uint64_t ex = x1 > x2 ? x1 : x2;
			for (auto cx = sx; cx <= ex; ++cx)
			{
				add_point(points, cx, y1);
			}
		}
		else
		{
			uint64_t dx = x1 > x2 ? -1 : 1;
			uint64_t dy = y1 > y2 ? -1 : 1;
			uint64_t l = x1 > x2 ? x1 - x2 : x2 - x1;
			
			for (auto cx = x1, cy = y1, idx = 0ull; idx <= l; cx += dx, cy += dy, idx++)
			{
				add_point(points, cx, cy);
			}
		}
	}

	uint64_t danger_points = 0;
	for (auto& thing : points)
	{
		if (thing.second >= 2)
		{
			danger_points++;
		}
	}

	std::cout << "part2 = " << danger_points << "\n";
}

int main()
{
	part1();
	part2();
}
