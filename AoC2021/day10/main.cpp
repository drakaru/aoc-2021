// day10.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std::string_literals;

std::unordered_map<char, std::pair<char, uint64_t>> syntax_check{
	{')', {'(', 3}},
	{']', {'[', 57}},
	{'}', {'{', 1197}},
	{'>', {'<', 25137}}
};

std::unordered_map<char, uint64_t> auto_complete{
	{'(', 1},
	{'[', 2},
	{'{', 3},
	{'<', 4},
};

void part1()
{
	auto f = std::ifstream("day10.txt");
	std::string line;
	uint64_t score = 0;

	while (std::getline(f, line))
	{
		std::stack<char> nav{};
		for (auto c : line)
		{
			switch (c) 
			{
			case '(':
			case '[':
			case '{':
			case '<':
				nav.push(c);
				break;
			default:
				if (syntax_check[c].first != nav.top())
				{
					score += syntax_check[c].second;
				}
				nav.pop();
			}
		}
	}
	
	std::cout << "part1 = " << score << "\n";
}

void part2()
{
	auto f = std::ifstream("day10.txt");
	std::string line;
	std::vector<uint64_t> scores{};
	while (std::getline(f, line))
	{
		std::stack<char> nav{};
		uint64_t score = 0;
		
		for (auto c : line)
		{
			if (auto_complete.contains(c))
			{
				nav.push(c);
			}
			else if (syntax_check[c].first != nav.top())
			{
				goto loopend;
			}
			else
			{
				nav.pop();
			}
		}
		
		while (!nav.empty())
		{
			score = score * 5 + auto_complete[nav.top()];
			nav.pop();	
		}

		scores.push_back(score);
	loopend:
		;
	}

	std::sort(scores.begin(), scores.end());
	auto result = scores[scores.size()/2];
	std::cout << "part2 = " << result << "\n";
}

int main()
{
	part1();
	part2();
}

