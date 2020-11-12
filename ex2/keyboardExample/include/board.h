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
	void print() const;
	bool SetBoard();
	int getlevelsize() const;
	vector<vector<char>>getvector() const;
	char getSqureData(Location cell) const;

private:
	vector<vector<char>> m_gameboard;
	int m_levelSize;
};