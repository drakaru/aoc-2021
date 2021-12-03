// day03.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <vector>
#include <bitset>
#include <numeric>
#include <algorithm>

using namespace std::string_literals;

const size_t linelength = 12;
using Line = std::bitset<linelength>;

void part1()
{
	auto f = std::ifstream("day03.txt");
	size_t lines = 0;
	
	std::array<uint64_t, linelength> nset{};
	Line line;

	while (!f.eof())
	{
		f >> line;
		
		for (size_t idx = 0; idx < linelength; ++idx)
		{
			nset[idx] += line[idx];
		}

		lines++;
	}

	auto hl = lines >> 1;
	
	Line gamma{};
	
	for (size_t idx = linelength; idx > 0; --idx)
	{
		if (nset[idx - 1] > hl)
		{
			gamma.set(idx - 1, true);
		}
	}
	uint64_t g = gamma.to_ullong();
	uint64_t e = (~gamma).to_ullong();

	auto result = g * e;

	std::cout << "part1 = " << result << "\n";
}

void part2()
{
	auto f = std::ifstream("day03.txt");
	
	std::vector<Line> lines{};
	Line line;

	while (!f.eof())
	{
		f >> line;
		lines.push_back(line);
	}

	std::vector<Line> most_common(lines);
	std::vector<Line> least_common(lines);

	size_t idx = linelength;
	while (idx > 0)
	{
		size_t count = 0;
		for (auto& line : most_common)
		{
			count += line[idx - 1];
		}

		auto notset = most_common.size() - count;
		bool mc = count >= notset;

		// should've used:
		// std::erase_if(most_common, [&](auto l) { return l.test(idx - 1) != mc; });
		/*most_common.erase(std::remove_if(
			most_common.begin(),
			most_common.end(),
			[idx,mc](Line l) {
				return l.test(idx - 1) != mc;
			}
		), most_common.end());*/
		
		idx--;
		if (most_common.size() == 1)
		{
			break;
		}
	}

	idx = linelength;
	while (idx > 0)
	{
		size_t count = 0;
		for (auto& line : least_common)
		{
			count += line[idx - 1];
		}

		auto notset = least_common.size() - count;
		bool mc = count < notset;

		// should've used: 
		// std::erase_if(least_common, [&](auto l) { return l.test(idx - 1) != mc; });
		least_common.erase(std::remove_if(
			least_common.begin(),
			least_common.end(),
			[idx, mc](Line l) {
				return l.test(idx - 1) != mc;
			}
		), least_common.end());
		
		idx--;
		if (least_common.size() == 1)
		{
			break;
		}
	}

	auto o2 = most_common[0].to_ulong();
	auto co2 = least_common[0].to_ulong();

	std::cout << "o2 = " << o2 << "\n";
	std::cout << "co2 = " << co2 << "\n";
	std::cout << "part2 = " << o2 * co2 << "\n";
}

int main()
{
	part1();
	part2();
}
