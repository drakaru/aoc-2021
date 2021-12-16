// day13.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <unordered_set>
#include <charconv>
#include <vector>
#include <cassert>

struct Point
{
	size_t x;
	size_t y;

	constexpr bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
};

template<>
struct std::hash<Point>
{
	std::size_t operator()(Point const& p) const noexcept
	{
		return p.y * 4096 + p.x;
	}
};


struct Fold
{
	char axis;
	size_t value;

	std::unordered_set<Point> fold(std::unordered_set<Point> const& dots) const
	{
		std::unordered_set<Point> folded{};

		for (auto const& p : dots)
		{
			Point other{p.x, p.y};

			if (axis == 'x' && other.x > value)
			{
				other.x = value - (other.x - value);
				assert(p.x > other.x);
			}
			else if(axis == 'y' && other.y > value)
			{
				other.y = value - (other.y - value);
				assert(p.y > other.y);
			}
			
			folded.insert(other);
		}

		return folded;
	}
};

void dump_grid(std::unordered_set<Point> const& dots, Fold const& fold)
{
	size_t mx = 0, my = 0;
	for (auto const& d : dots)
	{
		mx = std::max(d.x, mx);
		my = std::max(d.y, my);
	}

	for (size_t y = 0; y <= my; ++y)
	{
		if (fold.axis == 'y' and fold.value == y)
		{
			std::cout << std::string(mx+1, '-');
		}
		else
		{
			for (size_t x = 0; x <= mx; ++x)
			{
				if (fold.axis == 'x' and fold.value == x)
				{
					std::cout << '|';
				}
				else {
					std::cout << (dots.contains(Point{ x,y }) ? '#' : '.');
				}
			}
		}
			
		//std::cout << "\n";
	}
	//std::cout << "\n\n\n\n\n";
}

void dump_grid(std::unordered_set<Point> const& dots)
{
	size_t mx = 0, my = 0;
	for (auto const& d : dots)
	{
		mx = std::max(d.x, mx);
		my = std::max(d.y, my);
	}

	//std::cout << "dots " << dots.size() << ". mx: " << mx << " my: " << my << "\n";

	for (size_t y = 0; y <= my; ++y)
	{
		for (size_t x = 0; x <= mx; ++x)
		{
			std::cout << (dots.contains(Point{ x,y }) ? '#' : '.');
		}
		std::cout << "\n";
	}	
}

int main()
{
	std::unordered_set<Point> dots{};
	std::vector<Fold> folds{};
	auto f = std::ifstream("day13.txt");
	std::string line;
	while (std::getline(f, line))
	{
		//std::cout << line;

		if (line.size() == 0)
		{
			//std::cout << "\n";
			continue;
		}

		if (line[0] == 'f') // fold
		{

			char axis = line[11];
			size_t value;
			std::from_chars(line.data() + 13, line.data() + line.size(), value);
			folds.push_back(Fold{ axis, value });

			//std::cout << ": fold(" << axis << "," << value << ")";
		}
		else if (line.size())
		{
			auto idx = line.find(',');
			size_t x, y;
			std::from_chars(line.data(), line.data() + idx, x);
			std::from_chars(line.data() + idx + 1, line.data() + line.size(), y);

			dots.insert(Point{ x,y });

			//std::cout << ": dot(" << x << "," << y << ")";
		}

		//std::cout << "\n";
	}

	//std::cout << "\n";
	
	for (auto const& fold : folds)
	{
		//dump_grid(dots, fold);
		dots = fold.fold(dots);
		std::cout << dots.size() << "\n";
	}

	dump_grid(dots);
}
