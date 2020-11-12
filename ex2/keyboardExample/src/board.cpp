#include "board.h"

board::board()
{
	SetBoard();
}

bool board::SetBoard()
{
	ifstream Bfile;
	Bfile.open("Board.txt");
	if (!Bfile.is_open())
		return false;
	m_levelSize = (Bfile.get() - '0');
	char squre;
	Bfile.get();
	for (int row = 0; row < m_levelSize; ++row)
	{
		vector<char>temp;//to get board line
		for (int col = 0; col < m_levelSize; ++col)
		{
			Bfile.get(squre);
			if (squre == '\n')
				break;
			if (squre == '@')
			{

			}
			temp.push_back(squre);
		}
		Bfile.get();//skip the '\n'
		m_gameboard.push_back(temp);
	}
	return true;
}

int board::getlevelsize() const
{
	return m_levelSize;
}

std::vector<vector<char>> board::getvector() const
{
	return m_gameboard;
}

char board::getSqureData(Location cell) const
{
	return m_gameboard[cell.row][cell.col];
}

board::~board()
{

}

void board::print() const
{
	for (int row = 0; row < m_gameboard.size(); ++row)
	{
		for (int col = 0; col < m_gameboard[row].size(); ++col)
		{
			cout << m_gameboard[row][col];
		}
		cout << endl;
	}
}
