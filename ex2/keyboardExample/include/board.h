#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Location.h"

using std::iostream;
using std::ifstream;
using std::istream;
using std::vector;
using std::cout;
using std::endl;

class board
{
public:
	board();
	~board();
	void print();
	bool SetBoard();

private:
	vector<vector<char>> m_gameboard;
	int m_levelSize;
};