// day01.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <numeric>

using namespace std::string_literals;

void part1()
{
	auto f = std::ifstream("day01.txt");
	std::string line;
	auto prevDepth = 0ull;
	auto increases = 0ull;
	while (std::getline(f, line))
	{
		auto depth = std::stoul(line);
		if (prevDepth && depth > prevDepth)
		{
			increases++;
		}
		prevDepth = depth;
	}
	std::cout << "p1: " << increases << "\n";
}

void part2()
{
	auto f = std::ifstream("day01.txt");
	std::string line;

	std::array<uint64_t, 3> depths{};
	std::getline(f, line);
	depths[0] = std::stoul(line);
	std::getline(f, line);
	depths[1] = std::stoul(line);
	std::getline(f, line);
	depths[2] = std::stoul(line);

	auto increases = 0ull;
	auto prevDepth = std::accumulate(depths.begin(), depths.end(), 0ull);

	size_t idx = 0;
	while (std::getline(f, line))
	{
		depths[idx] = std::stoul(line);
		auto depth = std::accumulate(depths.begin(), depths.end(), 0ull);
		if (depth > prevDepth)
		{
			increases++;
		}
		idx = (idx + 1) % 3;
		prevDepth = depth;
	}
	std::cout << "p2: " << increases << "\n";
}

int main()
{
	part1();
	part2();

	return 0;
}
