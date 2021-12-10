// day09.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std::string_literals;

struct Point
{
	size_t x;
	size_t y;
	Point() = default;
	Point(size_t x, size_t y) { this->x = x; this->y = y; };
};

bool is_low(auto const& lines, auto x, auto y, auto w, auto h)
{
	auto xy = lines[y][x];
	if ((!x || lines[y][x - 1] > xy) &&
		(!y || lines[y - 1][x] > xy) &&
		(x == (w - 1) || lines[y][x + 1] > xy) &&
		(y == (h - 1) || lines[y + 1][x] > xy))
	{
		return true;
	}
	return false;
}

void part1(std::vector<std::string> const& lines, size_t w, size_t h)
{
	uint64_t risk = 0;

	for (size_t y = 0; y < h; ++y)
	{
		for (size_t x = 0; x < w; ++x)
		{
			if (is_low(lines, x, y, w, h))
			{
				risk += 1 + (lines[y][x] - '0');
			}
		}
	}
	
	std::cout << "part1 = " << risk << "\n";
}


uint64_t flood(auto const& lines, auto& checked, auto x, auto y, auto w, auto h)
{
	uint64_t total = 1;

	std::vector<bool> checked(w * h);
	std::vector<Point> found{ Point(x, y) };

	checked[y * w + x] = true;
	
	do
	{
		std::vector<Point> found2{};
		for (Point p : found)
		{
			if (p.x && !checked[(p.y) * w + p.x - 1] && lines[p.y][p.x - 1] < '9')
			{
				found2.push_back(Point(p.x - 1, p.y));
				checked[p.y * w + p.x - 1] = true;
			}
			if (p.y && !checked[(p.y - 1) * w + p.x] && lines[p.y - 1][p.x] < '9')
			{
				found2.push_back(Point(p.x, p.y - 1));
				checked[(p.y - 1) * w + p.x] = true;
			}
			if (p.x < (w - 1) && !checked[p.y * w + p.x + 1] && lines[p.y][p.x + 1] < '9')
			{
				found2.push_back(Point(p.x + 1, p.y));
				checked[p.y * w + p.x + 1] = true;
			}
			if (p.y < (h - 1) && !checked[(p.y + 1) * w + p.x] && lines[p.y + 1][p.x] < '9')
			{
				found2.push_back(Point(p.x, p.y + 1));
				checked[(p.y + 1) * w + p.x] = true;
			}	
		}

		found = found2;
		total += found.size();
		
	} while (found.size());

	return total;
}

uint64_t less_ugly_flood(auto const& lines, auto& checked, auto x, auto y, auto w, auto h)
{
	std::vector<Point> found_prev{ Point(x, y) };
	uint64_t total = 1;
	checked[y * w + x] = true;

	auto value_at = [&](auto const& p) { return lines[p.y][p.x]; };
	auto check = [&](auto const& p)
	{
		// abuse unsigned underflow
		if (p.x >= w || p.y >= h)
			return true;

		auto idx = p.y * w + p.x;
		bool c = checked[idx];
		checked[idx] = true;
		return c;
	};

	do
	{
		std::vector<Point> found_this{};

		for (auto const& p : found_prev)
		{
			std::array<Point, 4> to_check = {
				Point(p.x - 1, p.y),
				Point(p.x + 1, p.y),
				Point(p.x, p.y - 1),
				Point(p.x, p.y + 1),
			};

			std::for_each(to_check.begin(), to_check.end(), [&](auto const& o) {
				if (!check(o) && value_at(o) < '9')
				{
					found_this.push_back(o);
				}
			});
		}

		found_prev = found_this;
		total += found_prev.size();

	} while (found_prev.size());

	return total;
}

void part2(std::vector<std::string> const& lines, size_t w, size_t h)
{
	std::vector<uint64_t> basins{};
	std::vector<bool> checked(w * h);
	
	for (size_t y = 0; y < h; ++y)
	{
		for (size_t x = 0; x < w; ++x)
		{
			if (is_low(lines, x, y, w, h))
			{
				//basins.push_back(flood(lines, checked, x, y, w, h));
				basins.push_back(less_ugly_flood(lines, checked, x, y, w, h));
			}
		}
	}

	std::sort(basins.rbegin(), basins.rend());
	auto result = basins[0] * basins[1] * basins[2];
	std::cout << "part2 = " << result << "\n";
}

int main()
{
	auto f = std::ifstream("day09.txt");
	std::string line;
	std::vector<std::string> lines{};

	while (std::getline(f, line))
	{
		lines.push_back(line);
	}

	size_t w = lines[0].size();
	size_t h = lines.size();

	part1(lines, w, h);
	part2(lines, w, h);
}
