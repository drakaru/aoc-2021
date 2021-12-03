// day02.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <array>

using namespace std::string_literals;

void part1()
{
	auto f = std::ifstream("day02.txt");
	
	int h = 0;
	int d = 0;
	std::string direction;
	int magnitude;

	while (!f.eof())
	{
		f >> direction >> magnitude;
		switch (direction[0]) {

		case 'f':
			h += magnitude;
			break;
		case 'd':
			d += magnitude;
			break;
		case 'u':
			d -= magnitude;
			break;
		}

	}

	std::cout << "h * d = " << h * d << "\n";
}


void part2()
{
	auto f = std::ifstream("day02.txt");

	int h = 0;
	int d = 0;
	int a = 0;
	std::string direction;
	int magnitude;

	while (!f.eof())
	{
		f >> direction >> magnitude;
		switch (direction[0]) {

		case 'f':
			h += magnitude;
			d += magnitude * a;
			break;
		case 'd':
			a += magnitude;
			break;
		case 'u':
			a -= magnitude;
			break;
		}

	}

	std::cout << "h * d = " << h * d << "\n";
}

int main()
{
	part1();
	part2();
}
