// day07.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <vector>
#include <numeric>
#include <algorithm>
#include <charconv>
#include <sstream>
#include <iterator>

using namespace std::string_literals;


template<typename T>
std::vector<T> extract(const std::string& csv, char delim = ',')
{
	std::vector<T> vec{};
	std::stringstream aaaaa(csv);
	std::string item;
	while (std::getline(aaaaa, item, delim)) {
		T n;
		std::from_chars(item.data(), item.data() + item.size(), n);
		vec.push_back(n);
	}
	return vec;
}

void part1(const std::vector<int>& input)
{
	// lazy 
	auto low = *(std::min_element(input.cbegin(), input.cend()));
	auto high = *(std::max_element(input.cbegin(), input.cend()));
	auto lowest_tot = INT_MAX;
	
	for (auto x = low; x < high; x++)
	{
		auto tot = std::accumulate(input.cbegin(), input.cend(), 0, [x](auto s, auto crab) { return s + std::abs(x - crab); });
		lowest_tot = std::min(lowest_tot, tot);
	}

	std::cout << "part1 = " << lowest_tot << "\n";
}

void part2(const std::vector<int>& input)
{
	auto low = *(std::min_element(input.cbegin(), input.cend()));
	auto high = *(std::max_element(input.cbegin(), input.cend()));
	auto lowest_tot = INT_MAX;

	for (auto x = low; x < high; x++)
	{
		// lazy again :D
		auto tot = std::accumulate(input.cbegin(), input.cend(), 0, [x](auto s, auto crab) { 
			auto dist = std::abs(x - crab);
			auto dtot = dist;
			for (auto d = 0; d < dist; d++)
			{
				dtot += d;
			}
			return s + dtot;
		});
		lowest_tot = std::min(lowest_tot, tot);
	}

	std::cout << "part2 = " << lowest_tot << "\n";
}

int main()
{
	auto f = std::ifstream("day07.txt");
	std::string line;
	std::getline(f, line);
	auto input = extract<int>(line);

	part1(input);
	part2(input);
}

