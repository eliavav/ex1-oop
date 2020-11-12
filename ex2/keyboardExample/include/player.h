#pragma once

#include "Location.h"
#include "board.h"
#include "macros.h"
#include "io.h"

class player
{
public:
	player(Location curr);
	~player();
	bool setLocation(const board& board, Location curr);
	void movePlayer(const board& board);
	bool doMovment(const board& board, char c);
	Location getLocation() const;

private:
	bool checkvaldity(const board& board, Location curr);
	Location m_currentLocation;
};
