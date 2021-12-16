// day14.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <numeric>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <unordered_map>

using Pair = std::pair<char, char>;
using Rule = std::pair<std::array<char, 2>, char>;
using RuleSet = std::set<Rule>;
using Polymer = std::map<Pair, size_t>;

Polymer from_string(std::string const& polymer_str, RuleSet const& rules)
{
	Polymer polymer{};

	for (size_t idx = 0; idx < polymer_str.size() - 1; ++idx)
	{
		Pair ab = {polymer_str[idx], polymer_str[idx + 1]};
		polymer[ab]++;
	}

	return polymer;
}


Polymer polymer_advance(Polymer const& polymer, RuleSet const& rules)
{
	Polymer new_polymer{};

	for (auto const& rule : rules)
	{
		char a = rule.first[0];
		char b = rule.first[1];
		char c = rule.second;

		Pair ab = { a, b };
		Pair ac = { a, c };
		Pair cb = { c, b };
		
		if (polymer.contains(ab))
		{
			size_t ab_count = polymer.at(ab);
			new_polymer[ac] += ab_count;
			new_polymer[cb] += ab_count;
		}
	}
	
	return new_polymer;
}

size_t poly_low_high(Polymer const& polymer, std::string const& original_polymer)
{
	std::unordered_map<char, size_t> counts{};
	for (auto const& what : polymer)
	{
		counts[what.first.first] += what.second;
	}
	counts[original_polymer[original_polymer.size() - 1]]++;

	size_t low_count = std::numeric_limits<size_t>::max();
	size_t high_count = 0;

	for (auto const& c : counts)
	{
		auto s = c.second;
		if (s != 0)
		{
			if (s > high_count)
			{
				high_count = s;
			}
			if (s < low_count)
			{
				low_count = s;
			}
		}
	}
	return high_count - low_count;
}

void part1()
{
	auto f = std::ifstream("day14.txt");
	std::string polymer;
	std::string rule;
	std::getline(f, polymer);
	std::getline(f, rule);

	RuleSet ruleSet{};
	
	while (std::getline(f, rule))
	{
		ruleSet.insert({ {rule[0], rule[1]}, rule[6] });
	}

	Polymer p = from_string(polymer, ruleSet);

	for (size_t iteration = 0; iteration < 10; ++iteration)
	{
		p = polymer_advance(p, ruleSet);
	}

	auto result = poly_low_high(p, polymer);

	std::cout << "part1 = " << result << "\n";
}

void part2()
{
	auto f = std::ifstream("day14.txt");
	std::string polymer;
	std::string rule;
	std::getline(f, polymer);
	std::getline(f, rule);

	RuleSet ruleSet{};

	while (std::getline(f, rule))
	{
		ruleSet.insert({ {rule[0], rule[1]}, rule[6] });
	}

	Polymer p = from_string(polymer, ruleSet);

	for (size_t iteration = 0; iteration < 40; ++iteration)
	{
		p = polymer_advance(p, ruleSet);
	}

	auto result = poly_low_high(p, polymer);

	std::cout << "part2 = " << result << "\n";
}

int main()
{
	part1();
	part2();
}
