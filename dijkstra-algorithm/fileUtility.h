#ifndef DIJKSTRA_ALGORITHM_FILEUTILITY_H
#define DIJKSTRA_ALGORITHM_FILEUTILITY_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>


class Board
{
public:

	Board()
	{
		constexpr int ASCII_CORRECTION = 48;
		std::ifstream file(FILE_NAME_);
		std::string line;

		while (std::getline(file, line))
		{
			std::vector<int> lineInt;

			for(const auto digit : line)
				lineInt.push_back( static_cast<int>(digit) - ASCII_CORRECTION );

			board_.push_back(lineInt);
		}
	}

	void print()
	{
		for(const auto & row : board_)
		{
			for(const auto & digit : row)
				std::cout<< digit;

			std::cout<<std::endl;
		}
	}

	std::vector< std::vector<int> > getBoard()
	{
		return board_;
	}

private:
	std::vector< std::vector<int> > board_;
	const std::string FILE_NAME_ = "..\\..\\board.txt";

};

#endif //DIJKSTRA_ALGORITHM_FILEUTILITY_H
