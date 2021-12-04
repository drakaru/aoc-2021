// day04.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <charconv>
#include <sstream>

using namespace std::string_literals;

using Line = std::array<uint16_t, 5>;

class Board
{
	std::array<Line, 5> rows{};
	std::array<Line, 5> cols{};
public:
	Board(const std::array<uint16_t, 25>& numbers)
	{
		for (uint16_t x = 0; x < 5; ++x)
		{
			for (uint16_t y = 0; y < 5; ++y)
			{
				rows[x][y] = numbers[y + x * 5];
				cols[x][y] = numbers[y * 5 + x];
			}
		}
	}

	bool has_won(const std::vector<uint16_t>& called) const
	{
		for (const auto& row : rows)
		{
			uint8_t found = 0;
			for (auto x : row)
			{				
				for (auto n : called)
				{
					if (x == n)
					{
						found++;
						break;
					}
				}	
			}
			if (found == 5)
			{
				return true;
			}	
		}

		for (const auto& col : cols)
		{
			uint8_t found = 0;
			for (auto x : col)
			{
				for (auto n : called)
				{
					if (x == n)
					{
						found++;
						break;
					}
				}
			}
			if (found == 5)
			{
				return true;
			}
		}

		
		return false;
	}

	uint64_t score(const std::vector<uint16_t>& called) const
	{
		uint16_t last_called = called.back();
		uint64_t total = 0;

		for (const auto& col : cols)
		{
			for (auto x : col)
			{
				bool found = false;
				for (auto n : called)
				{
					if (x == n)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					total += x;
				}
			}
		}

		return last_called * total;
	}
};

const Board* winning_board(const auto& boards, const auto& called)
{
	for (const Board& b : boards)
	{
		if (b.has_won(called))
		{
			return &b;
		}
	}
	return nullptr;
}

template<typename T>
void extract(const std::string& csv, std::vector<T>& vec, char delim=',')
{
	std::stringstream aaaaa(csv);
	std::string item;
	while (getline(aaaaa, item, delim)) {
		T n;
		std::from_chars(item.data(), item.data() + item.size(), n);
		vec.push_back(n);
	}
}

void part1(const std::vector<uint16_t>& to_call, const std::vector<Board>& boards)
{
	std::vector<uint16_t> called{};

	uint64_t result = 0;
	
	for (uint16_t n : to_call)
	{
		called.push_back(n);
		if (called.size() >= 5)
		{
			const Board* b = winning_board(boards, called);
			if (b)
			{
				std::cout << "part1 = " << b->score(called) << "\n";
				return;
			}
		}
	}
}

void part2(const std::vector<uint16_t>& to_call, std::vector<Board> boards)
{
	std::vector<uint16_t> called{};
	auto iter = to_call.cbegin();

	while (boards.size() > 1)
	{
		called.push_back(*iter++);
		std::erase_if(boards, [called](auto b) { return b.has_won(called); });
	}
	while (!boards[0].has_won(called))
	{
		called.push_back(*iter++);
	}
	
	std::cout << "part2 = " << boards[0].score(called) << "\n";
}

int main()
{
	auto f = std::ifstream("day04.txt");

	std::vector<Board> boards;
	std::vector<uint16_t> to_call{};

	std::string line{};
	std::getline(f, line);
	extract(line, to_call);

	while (!f.eof())
	{
		std::array<uint16_t, 25> numbers{};
		for (uint16_t x = 0; x < 25; ++x)
		{
			uint16_t n;
			f >> n;
			numbers[x] = n;
		}
		Board board = Board(numbers);
		boards.push_back(board);
	};

	part1(to_call, boards);
	part2(to_call, boards);
}
