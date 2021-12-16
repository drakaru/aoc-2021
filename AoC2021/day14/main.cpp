// day14.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <limits>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

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
		char c = rule.second;//insert

		Pair ab = {a,b};
		if (polymer.contains(ab))
		{
			size_t ab_count = polymer.at(ab);
			new_polymer[{a,c}] += ab_count;
			new_polymer[{c,b}] += ab_count;
		}
	}
	
	return new_polymer;
}

size_t poly_count(Polymer const& polymer, std::string const& original_polymer)
{
	// map the counts of the first character of each pair
	// suppose ruleset consists of pairs AB and AD, then count(A) = count(AB) + count(AD)
	std::unordered_map<char, size_t> counts{};

	// counting only the first character of each pair misses the final character of the polymer
	// this will always match the final character of the original polymer, so take it from there
	counts[original_polymer[original_polymer.size() - 1]]++;
	
	for (auto const& pair_size : polymer)
	{
		counts[pair_size.first.first] += pair_size.second;
	}

	const auto [low_count, high_count] = std::minmax_element(
		cbegin(counts), 
		cend(counts), 
		[](auto const& a, auto const& b) { return a.second < b.second; }
	);

	return high_count->second - low_count->second;
}

int main()
{
	std::string original_polymer;
	RuleSet rules{};
	{
		auto f = std::ifstream("day14.txt");

		std::string rule;
		std::getline(f, original_polymer);
		std::getline(f, rule);
		
		while (std::getline(f, rule))
		{
			// fixed size rules, ie: CN -> C
			rules.insert({ {rule[0], rule[1]}, rule[6] });
		}
	}
	
	Polymer polymer = from_string(original_polymer, rules);

	auto advance_and_count = [&](size_t const times) -> size_t
	{
		for (size_t iteration = 0; iteration < times; ++iteration)
		{
			polymer = polymer_advance(polymer, rules);
		}
		return poly_count(polymer, original_polymer);
	};
	
	std::cout << "part1: " << advance_and_count(10) << "\n";
	std::cout << "part2: " << advance_and_count(30) << "\n";

}
