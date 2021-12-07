// day06.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <cstdint>
#include <numeric>
#include <charconv>
#include <sstream>
#include <bitset>

using namespace std::string_literals;
using LanternState = std::array<uint64_t, 9>;

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

uint64_t simulate(const LanternState& initial_state, uint16_t days)
{
	LanternState state(initial_state);

	for (uint16_t day = 0; day < days; day++)
	{
		LanternState copy{};
		for (uint16_t t = 10; t < 19; t++)
		{
			copy[t - 10] = state[t % 9];
		}
		copy[6] += state[0];

		state = copy;
	}

	return std::accumulate(state.begin(), state.end(), 0ull);
}

int main()
{
	auto f = std::ifstream("day06.txt");
	
	std::string line;
	std::getline(f, line);
	
	LanternState state{};

	for (auto x : extract<uint16_t>(line))
	{
		state[x] += 1;
	}

	std::cout << "part 1: " << simulate(state, 80) << "\n";
	std::cout << "part 2: " << simulate(state, 256) << "\n";
}
