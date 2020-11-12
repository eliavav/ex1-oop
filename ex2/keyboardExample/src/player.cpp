#include "player.h"


player::player(Location curr) : m_currentLocation(curr)
{
}

player::~player()
{
}

bool player::setLocation(const board& board, Location curr)
{
	if (checkvaldity(board, curr))
		m_currentLocation = curr;
}

void player::movePlayer(const board& board)
{
	auto c = Keyboard::getch();
	while (true)
	{
		if (c == SPECIAL_KEY)
			if (doMovment(board, c))
				break;
		auto c = Keyboard::getch();
	}

}

bool player::doMovment(const board& board, char c)
{
	switch (c)
	{
	case KB_UP:
		Location to_move(m_currentLocation.row, m_currentLocation.row - 1);
		return setLocation(board, to_move);
		break;

	case KB_DOWN:
		Location to_move(m_currentLocation.row, m_currentLocation.row + 1);
		return setLocation(board, to_move);


	}
}

Location player::getLocation() const
{
	return m_currentLocation;
}

bool player::checkvaldity(const board& board, Location curr)
{
	if (curr.row < 1 || curr.col < 2 || curr.row >= board.getlevelsize() - 1 || curr.col > board.getlevelsize() - 1)
		return false;
	return true;
}




