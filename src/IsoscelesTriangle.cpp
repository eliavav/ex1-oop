#include "IsoscelesTriangle.h"

//---------------------------------------------------------------------------------
//constructer for IsoscelesTriangle, that get 3 dots.
IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
{
	if (isvalidIsoscelesTriangle(vertices[0], vertices[1], vertices[2]))
	{
		m_BottomLeft = vertices[0];
		m_BottomRight = vertices[1];
		m_Middle = vertices[2];
	}
	else
		defultset();
}

//---------------------------------------------------------------------------------
//constructor for IsoscelesTriangle that get 2 dots and the height.
IsoscelesTriangle::IsoscelesTriangle(const Vertex& v0, const Vertex& v1, double height)
{
	Vertex vertices[3];
	vertices[0].m_col = v0.m_col;
	vertices[0].m_row = v0.m_row;
	vertices[1].m_col = v1.m_col;
	vertices[1].m_row = v1.m_row;
	vertices[2].m_col = (v1.m_col - v0.m_col) / 2;
	vertices[2].m_row = v0.m_row + height;//y value of the base + height

	IsoscelesTriangle((const Vertex*)vertices);
}

//---------------------------------------------------------------------------------
//func that return 1 of the triangle dots acoording to the input
Vertex IsoscelesTriangle::getVertex(int index) const
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

//---------------------------------------------------------------------------------
//get the base lenght
double IsoscelesTriangle::getBaseLength() const
{
	return (m_BottomRight.m_col - m_BottomLeft.m_col); //calculate the base length 
}

//---------------------------------------------------------------------------------
//get the leg of the IsoscelesTriangle 
double IsoscelesTriangle::getLegLength() const
{
	double height = getHeight();
	double length = getBaseLength() / 2;
	return sqrt(height * height + length * length);
}

//---------------------------------------------------------------------------------
//get IsoscelesTriangle heiht
double IsoscelesTriangle::getHeight() const
{
	return abs(m_Middle.m_row - m_BottomLeft.m_row);
}

//---------------------------------------------------------------------------------
//the the IsoscelesTriangle dots
void IsoscelesTriangle::draw(Board& board) const
{
	board.drawLine(m_Middle, m_BottomRight);//print first - top to right bottom
	board.drawLine(m_BottomRight, m_BottomLeft);//than print right to left
	board.drawLine(m_BottomLeft, m_Middle);//print from left bottom to top
}

//---------------------------------------------------------------------------------
//this func return 2 dots, the bottumLeft & topright of rectangle that boound the IsoscelesTriangle
Rectangle IsoscelesTriangle::getBoundingRectangle() const
{
	Vertex bottomleft,
		   topright;

	if (m_Middle.m_row > m_BottomLeft.m_row)//if the triangle is with base on bottom and top above
	{
		bottomleft.m_col = m_BottomLeft.m_col;
		bottomleft.m_row = m_BottomLeft.m_row;
		topright.m_col = m_BottomRight.m_col;
		topright.m_row = m_Middle.m_row;
	}	
	else//the base ontop and the top is below
	{
		bottomleft.m_col = m_BottomLeft.m_col;
		bottomleft.m_row = m_Middle.m_row;
		topright.m_col = m_BottomRight.m_col;
		topright.m_row = m_BottomRight.m_row;
	}
	Rectangle r1(bottomleft, topright);
	return r1;
}

//---------------------------------------------------------------------------------
//calculate the area of the IsoscelesTriangle
double IsoscelesTriangle::getArea() const
{
	return (getBaseLength() * getHeight()) / 2;
}

//---------------------------------------------------------------------------------
//calculate the perimeter of the IsoscelesTriangle
double IsoscelesTriangle::getPerimeter() const
{

	return getBaseLength()+ 2 * getLegLength();
}

//---------------------------------------------------------------------------------
////calculate the center dot of the IsoscelesTriangle
Vertex IsoscelesTriangle::getCenter() const
{
	Vertex center((m_BottomRight.m_col - m_BottomLeft.m_col) / 2 + m_BottomLeft.m_col,
				  (m_Middle.m_row - m_BottomLeft.m_row) / 2 + m_BottomLeft.m_row);
	return center;
}

//---------------------------------------------------------------------------------
//change the scale of the IsoscelesTriangle
bool IsoscelesTriangle::scale(double factor)
{
	if(factor < 0)
		return false;
	Vertex new_bottomLeft, new_bottomRight, new_topmiddle;
	Vertex center = getCenter();

	new_bottomLeft.m_col = (m_BottomLeft.m_col - center.m_col) * factor + center.m_col;
	new_bottomLeft.m_row = (m_BottomLeft.m_row - center.m_row) * factor + center.m_row;
	new_bottomRight.m_col = (m_BottomRight.m_col - center.m_col) * factor + center.m_col;
	new_bottomRight.m_row = (m_BottomRight.m_row - center.m_row) * factor + center.m_row;
	new_topmiddle.m_col = (m_Middle.m_col - center.m_col) * factor + center.m_col;
	new_topmiddle.m_row = (m_Middle.m_row - center.m_row) * factor + center.m_row;

	if (!isvalidIsoscelesTriangle(new_bottomLeft, new_bottomRight, new_topmiddle))
		return false;
	m_BottomLeft = new_bottomLeft;
	m_BottomRight = new_bottomRight;
	m_Middle = new_topmiddle;
	return true;
}

//---------------------------------------------------------------------------------
//check if the dots create a valid IsoscelesTriangle
bool IsoscelesTriangle::isvalidIsoscelesTriangle(const Vertex& left, const Vertex& right, const Vertex& middle)
{
	if (left.m_col > right.m_col || !left.isValid() || !right.isValid() || !middle.isValid()
		|| !(middle.m_col - (((right.m_col - left.m_col) / 2) + left.m_col) < 0.1 
		&& middle.m_col - (((right.m_col - left.m_col) / 2) + left.m_col) > -0.1))
		return false;
	return true;
}

//---------------------------------------------------------------------------------
//defult setting to IsoscelesTriangle, if the data is incorrect.
void IsoscelesTriangle::defultset()
{
	m_BottomLeft.m_col = 20;
	m_BottomLeft.m_row = 20;
	m_BottomRight.m_col = 30;
	m_BottomRight.m_row = 20;
	m_Middle.m_col = 25;
	m_Middle.m_row = 20+sqrt(75);
}
