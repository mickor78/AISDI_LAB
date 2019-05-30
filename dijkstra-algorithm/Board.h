#ifndef DIJKSTRA_ALGORITHM_FILEUTILITY_H
#define DIJKSTRA_ALGORITHM_FILEUTILITY_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <map>

enum class Turn{ RIGHT, DOWN, LEFT, UP };


class Vertex
{
public:
	Vertex()
	{
		edges_[0] = std::pair<int, Vertex*>(10, nullptr);
		edges_[1] = std::pair<int, Vertex*>(10, nullptr);
		edges_[2] = std::pair<int, Vertex*>(10, nullptr);
		edges_[3] = std::pair<int, Vertex*>(10, nullptr);
		isEnd_ = false;
	}

	void setRight(int cost, Vertex* nextVertex)
	{
		edges_[0] = std::pair<int, Vertex*>(cost, nextVertex);
	}

	void setDown(int cost, Vertex* nextVertex)
	{
		edges_[1] = std::pair<int, Vertex*>(cost, nextVertex);
	}

	void setLeft(int cost, Vertex* nextVertex)
	{
		edges_[2] = std::pair<int, Vertex*>(cost, nextVertex);
	}

	void setUp(int cost, Vertex* nextVertex)
	{
		edges_[3] = std::pair<int, Vertex*>(cost, nextVertex);
	}

	Vertex* getRight()
	{
		return edges_[0].second;
	}

	Vertex* getDown()
	{
		return edges_[1].second;
	}

	Vertex* getLeft()
	{
		return edges_[2].second;
	}

	Vertex* getUp()
	{
		return edges_[3].second;
	}

	std::pair<int,Vertex*>* getNeighbours()
	{
		return edges_;
	}

	bool isEnd()
	{
		return isEnd_;
	}

	void setEnd()
	{
		isEnd_ = true;
	}

private:
	std::pair<int,Vertex*> edges_[4];
	bool isEnd_;
};


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

		file.close();
		SIZE_ = board_.size();
		start_ = new Vertex();
	}

	void print()
	{
		std::cout<<std::endl;

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

	std::vector<Turn> getShortestWay()
	{/*
		std::vector<Turn> shortestWay;
		std::map< int,Turn > queue;

		for(auto & row : costMatrix)
			for(auto & cost : row)
				cost = 10;

		costMatrix[0][0] = 0;

*/
		return {};
	}

	void createGraph()
	{
		Vertex* node{}, * prev{}, * downNode{}, *upNode{};

		std::vector<Vertex*> heads;

		for(int i=0; i< SIZE_; ++i)
		{
			if (i == 0)
				heads.push_back(start_);
			else
				heads.push_back(new Vertex);
		}

		// populate two-dir, horizontal lists
		for(int i=0; i<SIZE_; ++i)
		{
			node = heads[i];

			for(int j=0; j<SIZE_; ++j)
			{
				if(j==0)
					node->setRight(board_[i][j+1], new Vertex);
				else if(j == (SIZE_ - 1))
					node->setLeft(board_[i][j-1], prev);
				else //if(j != (SIZE_ - 1))
				{
					node->setRight(board_[i][j+1], new Vertex);
					node->setLeft(board_[i][j-1], prev);
				}

				prev = node;
				node = node->getRight();
			}
		}

		// join lists
		for(int i=0; i<SIZE_; ++i)
		{
			node = heads[i];
			if(i != 0)
				upNode = heads[i-1];
			else
				upNode = nullptr;

			if(i != (SIZE_ - 1))
				downNode = heads[i+1];
			else
				downNode = nullptr;

			for(int j=0; j<SIZE_; ++j)
			{
				if(i==0)
					node->setDown(board_[i+1][j], downNode);
				else if(i == (SIZE_ - 1))
					node->setUp(board_[i-1][j], upNode);
				else //if(j != (SIZE_ - 1))
				{
					node->setDown(board_[i+1][j], downNode);
					node->setUp(board_[i-1][j], upNode);
				}

				if(downNode)
					downNode = downNode->getRight();
				if(upNode)
					upNode = upNode->getRight();
				node = node->getRight();
			}
		}
	}

private:

	std::vector< std::vector<int> > board_;
	Vertex* start_;
	unsigned int SIZE_;
	const std::string FILE_NAME_ = "..\\..\\board.txt";

};



#endif //DIJKSTRA_ALGORITHM_FILEUTILITY_H
