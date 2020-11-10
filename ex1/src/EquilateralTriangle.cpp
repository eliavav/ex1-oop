#include "EquilateralTriangle.h"

//-------------------------------------------------------------------------------------------------
//constructor
EquilateralTriangle::EquilateralTriangle(const Vertex vertices[3])
{
	if (isvalidEquilateralTriangle(vertices[0], vertices[1], vertices[2]))
	{
		m_BottomLeft = vertices[0];
		m_BottomRight = vertices[1];
		m_Middle = vertices[2];
	}
	else
		defultset();
}

//-------------------------------------------------------------------------------------------------
// print the Equilateral Triangle
void EquilateralTriangle::draw(Board& board) const
{
	board.drawLine(m_Middle, m_BottomRight);//print first - top to right bottom
	board.drawLine(m_BottomRight, m_BottomLeft);//than print right to left
	board.drawLine(m_BottomLeft, m_Middle);//print from left bottom to top
}

//------------------------------------------------------------------------------------------------- 
//check if the data is valid, and the input is a valid Equilateral Triangle
bool EquilateralTriangle::isvalidEquilateralTriangle(const Vertex& left, const Vertex& right, const Vertex& middle)
{
	if (!left.isValid() || !right.isValid() || !middle.isValid()
		|| !(middle.m_col - (((right.m_col - left.m_col) / 2) + left.m_col) < 0.1
			&& middle.m_col - (((right.m_col - left.m_col) / 2) + left.m_col) > -0.1)
		|| !((middle.m_row - left.m_row) - ((sqrt(3) / 2) * (right.m_col - left.m_col)) < 0.1
		&& (middle.m_row - left.m_row) - ((sqrt(3) / 2) * (right.m_col - left.m_col)) > -0.5))
		return false;

	return true;
}

//-------------------------------------------------------------------------------------------------
//get the asked dot of the triangle
Vertex EquilateralTriangle::getVertex(int index) const
{
	switch (index)
	{
	case 0:
		return m_BottomLeft;
	case 1:
		return m_BottomRight;
	case 2:
		return m_Middle;
	default:
	{
		Vertex vertex(0, 0);
		return vertex;
	}
	}
}

//-------------------------------------------------------------------------------------------------
//get the bounding rectangle for the Equilateral Triangle
Rectangle EquilateralTriangle::getBoundingRectangle() const
{
	Vertex bottomleft,
		topright;

	if (m_Middle.m_row > m_BottomLeft.m_row)//if the triangle is straight
	{
		bottomleft.m_col = m_BottomLeft.m_col;
		bottomleft.m_row = m_BottomLeft.m_row;
		topright.m_col = m_BottomRight.m_col;
		topright.m_row = m_Middle.m_row;
	}
	else//triangle is upside down
	{
		bottomleft.m_col = m_BottomLeft.m_col;
		bottomleft.m_row = m_Middle.m_row;
		topright.m_col = m_BottomRight.m_col;
		topright.m_row = m_BottomRight.m_row;
	}
	Rectangle r1(bottomleft, topright);
	return r1;
}

//-------------------------------------------------------------------------------------------------
//get the lenght of the Equilateral Triangle side
double EquilateralTriangle::getLength() const
{
	return m_BottomRight.m_col - m_BottomLeft.m_col;
}

//-------------------------------------------------------------------------------------------------
//get the area of the Equilateral Triangle
double EquilateralTriangle::getArea() const
{

	return abs((m_BottomRight.m_col - m_BottomLeft.m_col) * (m_Middle.m_row - m_BottomLeft.m_row) / 2);
}

//-------------------------------------------------------------------------------------------------
//get the perimiter of the Equilateral Triangle
double EquilateralTriangle::getPerimeter() const
{
	return (m_BottomRight.m_col - m_BottomLeft.m_col) * 3;
}

//-------------------------------------------------------------------------------------------------
//get the cender dot of the Equilateral Triangle
Vertex EquilateralTriangle::getCenter() const
{
	Vertex center((m_BottomRight.m_col - m_BottomLeft.m_col) / 2 + m_BottomLeft.m_col,
		(m_Middle.m_row - m_BottomLeft.m_row) / 2 + m_BottomLeft.m_row);
	return center;
}

//-------------------------------------------------------------------------------------------------
//set the new triangle with scaling
bool EquilateralTriangle::scale(double factor)
{
	if (factor < 0)
		return false;
	Vertex new_bottomLeft, new_bottomRight, new_topmiddle;
	Vertex center = getCenter();

	new_bottomLeft.m_col = (m_BottomLeft.m_col - center.m_col) * factor + center.m_col;
	new_bottomLeft.m_row = (m_BottomLeft.m_row - center.m_row) * factor + center.m_row;
	new_bottomRight.m_col = (m_BottomRight.m_col - center.m_col) * factor + center.m_col;
	new_bottomRight.m_row = (m_BottomRight.m_row - center.m_row) * factor + center.m_row;
	new_topmiddle.m_col = (m_Middle.m_col - center.m_col) * factor + center.m_col;
	new_topmiddle.m_row = (m_Middle.m_row - center.m_row) * factor + center.m_row;

	if (!isvalidEquilateralTriangle(new_bottomLeft, new_bottomRight, new_topmiddle))
		return false;
	m_BottomLeft = new_bottomLeft;
	m_BottomRight = new_bottomRight;
	m_Middle = new_topmiddle;
	return true;
}

//-------------------------------------------------------------------------------------------------
//defult setting fo the Equilateral Triangle, if there's somthing wrong with the data
void EquilateralTriangle::defultset()
{
	m_BottomLeft.m_col = 20;
	m_BottomLeft.m_row = 20;
	m_BottomRight.m_col = 30;
	m_BottomRight.m_row = 20;
	m_Middle.m_col = 25;
	m_Middle.m_row = 20 + sqrt(75);
}

