
#include "Rectangle.h"

//**********------------------------------------constractors-------------------------------------**********

Rectangle::Rectangle(const Vertex vertices[2])
{
	set(vertices[0], vertices[1]);
}

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
	set(bottomLeft, topRight);
}

//---------------------------------------------------------------------------------
Rectangle::Rectangle(double x0, double y0, double x1, double y1)
{
	Vertex bottomLeft(x0, y0), topRight(x1, y1);
	set(bottomLeft, topRight);
}

//---------------------------------------------------------------------------------
Rectangle::Rectangle(const Vertex& center, double width, double height)
{
	Vertex bottomLeft((center.m_col - width / 2), (center.m_row - height / 2)),
		   topRight((center.m_col + width / 2), (center.m_row + height / 2));

	set(bottomLeft, topRight);

	if (!isDataValid(width, height))
	{
		defultset();
	}
}

//end constructors---------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//draw lines on the board
void Rectangle::draw(Board& board) const
{
	Vertex topleft(m_BottomLeft.m_col, m_TopRight.m_row);
	Vertex bottomRight(m_TopRight.m_col, m_BottomLeft.m_row);
	board.drawLine(topleft, m_TopRight); //draw the upper line from topleft to topright 
	board.drawLine(m_TopRight, bottomRight); //draw the upper line from topright to bottomright
	board.drawLine(bottomRight, m_BottomLeft); //draw the upper line from bottomright to bottomLeft
	board.drawLine(m_BottomLeft, topleft); //draw the upper line from bottomleft to topLeft
}

//-------------------------------------------------------------------------------------------------
//change rectangke scale
bool Rectangle::scale(double factor)

{
	if (factor < 0)//negetive scale is not possible
		return false;

	Vertex new_bottomLeft, new_topRight;
	Vertex center = getCenter();

	new_bottomLeft.m_col = center.m_col - ((getWidth() * factor) / 2); //change the x bottomleft with scale 
	new_topRight.m_col = center.m_col + ((getHeight() * factor) / 2);//change the x topright with scale 
	new_bottomLeft.m_row = center.m_row - ((getWidth() * factor) / 2);//change the x bottomleft with scale
	new_topRight.m_row = center.m_row + ((getHeight() * factor) / 2);//change the y topright with scale 

	if (!new_bottomLeft.isValid() || !new_topRight.isValid())      //if the new dots creating valid rectangle
		return false;

	m_BottomLeft = new_bottomLeft;
	m_TopRight = new_topRight;

	return true;
}

//**********------------------------------------get functions-------------------------------------**********
//---------------------------------------------------------------------------------
//return rectangle's Bottom Left vertex
Vertex Rectangle::getBottomLeft() const
{
	return m_BottomLeft;
}

//---------------------------------------------------------------------------------
//return rectangle's Top Right vertex
Vertex Rectangle::getTopRight() const
{
	return m_TopRight;
}

//---------------------------------------------------------------------------------
//return rectangle's center
Vertex Rectangle::getCenter() const
{
	Vertex center(((m_BottomLeft.m_row + m_TopRight.m_row) / 2), ((m_BottomLeft.m_col + m_TopRight.m_col) / 2));
	return center;
}

//---------------------------------------------------------------------------------
//return the smallest blocking Rectangle
Rectangle Rectangle::getBoundingRectangle() const
{
	Rectangle r(m_BottomLeft, m_TopRight);
	return r;
}

//---------------------------------------------------------------------------------
//return the Rectangle's area
double Rectangle::getArea() const
{
	return getWidth() * getHeight();
}

//---------------------------------------------------------------------------------
//return the Rectangle's Perimeter
double Rectangle::getPerimeter() const
{
	return (getWidth() * 2 + getHeight() * 2);
}

//------------------------------------------------------------------------------------------
//
void Rectangle::set(const Vertex& bottomLeft, const Vertex& topRight)
{
	if (checkRctangleCond(bottomLeft, topRight))
	{
		m_BottomLeft.m_col = bottomLeft.m_col;
		m_BottomLeft.m_row = bottomLeft.m_row;
		m_TopRight.m_col = topRight.m_col;
		m_TopRight.m_row = topRight.m_row;
	}
	else
	{
		defultset();
	}

}

//---------------------------------------------------------------------------------
//defult set new rectangle with defult values. if we get false data.
void Rectangle::defultset()
{
	m_BottomLeft.m_col = 10;
	m_BottomLeft.m_row = 20;
	m_TopRight.m_col = 20;
	m_TopRight.m_row = 30;
}

//---------------------------------------------------------------------------------
//return rectangle's height
double Rectangle::getHeight() const
{
	return m_TopRight.m_row - m_BottomLeft.m_row;
}

//---------------------------------------------------------------------------------
//return rectangle's Width
double Rectangle::getWidth() const
{
	return m_TopRight.m_col - m_BottomLeft.m_col;
}
//**********--------------------------------------------------------------------------------------**********

//---------------------------------------------------------------------------------
//check if the two vertexes mintain all demands
bool Rectangle::checkRctangleCond(Vertex bottomLeft, Vertex topRight)
{
	return  (bottomLeft.isValid() &&
			 topRight.isValid() &&
			 topRight.isHigherThan(bottomLeft) && //to check if bottomLeft lower than topRight
			 topRight.isToTheRightOf(bottomLeft)); // //to check if bottomLeft righter than topRight)
}

//---------------------------------------------------------------------------------
//check that width and height positives
bool Rectangle::isDataValid(double width, double height)
{
	return (width >= 0 && height >= 0) ? true : false;
}

