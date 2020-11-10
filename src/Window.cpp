#include "Window.h"

//window contructor
Window::Window(const Rectangle& outer, const Rectangle& inner)
{
    if (isvalidWindow(outer, inner))
    {
        m_inner.set(inner.getBottomLeft(), inner.getTopRight());
        m_outer.set(outer.getBottomLeft(), outer.getTopRight());
    }
    else
    {
        defultset();
    }
}

//------------------------------------------------------------------------------------------
//inner rectangle constructor
Window::Window(const Rectangle& outer, double verticalThickness, double horizontalThickness)
{
    if (isvalidWindow(outer, verticalThickness, horizontalThickness))
    {
        Vertex outerBottomLeft = outer.getBottomLeft();//Instrumental variable to  get the outer rectangle dots
        Vertex outerTopRight = outer.getTopRight();//Instrumental variable to  get the outer rectangle dots
                //to claculate the inner rectangle dots and insert the data to the Instrumental variable
        Vertex bottomLeft(outerBottomLeft.m_col + horizontalThickness, outerBottomLeft.m_row + verticalThickness),
               topRight(outerTopRight.m_col - horizontalThickness, outerTopRight.m_row - verticalThickness);

        m_outer.set(outer.getBottomLeft(), outer.getTopRight()); //set the bottomLeft dot of the inner rectangle
        m_inner.set(bottomLeft, topRight);                      //set the bottomLeft dot of the inner rectangle
    }
    else
        defultset();
}

//------------------------------------------------------------------------------------------
//get the bottum left dot of the OUTSIDE triangle
Vertex Window::getBottomLeft() const
{
    return m_outer.getBottomLeft();
}

//------------------------------------------------------------------------------------------
//get the top right dot of the OUTSIDE triangle
Vertex Window::getTopRight() const
{
    return m_outer.getTopRight();
}

//------------------------------------------------------------------------------------------
//get the outer rectangle top right dot, and return the inside rectangle's dot.
double Window::getVerticalThickness() const
{
    Vertex outerTopRight = m_outer.getTopRight(),//Instrumental variable to  get the outer rectangle dots
           innerTopRight = m_inner.getTopRight();
    return outerTopRight.m_row - innerTopRight.m_row;
}

//------------------------------------------------------------------------------------------
//get the outer rectangle bottum left dot, and return the inside rectangle's dot.
double Window::getHorizontalThickness() const
{
    Vertex outerBottomeft = m_outer.getBottomLeft(),//Instrumental variable to  get the outer rectangle dots
           innerBottomleft = m_inner.getBottomLeft();
    return innerBottomleft.m_col - outerBottomeft.m_col;
}

//------------------------------------------------------------------------------------------
//print both inside and outside rectangle
void Window::draw(Board& board) const
{
    //to get all dots of the outer rectangle
    Vertex outerBottomLeft = m_outer.getBottomLeft(),
        outerTopRight = m_outer.getTopRight(),
        outerBottomRight(outerTopRight.m_col, outerBottomLeft.m_row),
        outerTopLeft(outerBottomLeft.m_col, outerTopRight.m_row),
        //to get all dots of inner rectngle
        innerBottomLeft = m_inner.getBottomLeft(),
        innerTopRight = m_inner.getTopRight(),
        innerBottomRight(innerTopRight.m_col, innerBottomLeft.m_row),
        innerTopLeft(innerBottomLeft.m_col, innerTopRight.m_row);
    //draw the outer rectangle
    board.drawLine(outerTopLeft, outerTopRight); //draw the upper line from topleft to topright 
    board.drawLine(outerTopRight, outerBottomRight); //draw the upper line from topright to bottomright
    board.drawLine(outerBottomRight, outerBottomLeft); //draw the upper line from bottomright to bottomLeft
    board.drawLine(outerBottomLeft, outerTopLeft); //draw the upper line from bottomleft to topLeft
          //draw th inner rectangle
    board.drawLine(innerTopLeft, innerTopRight); //draw the upper line from topleft to topright 
    board.drawLine(innerTopRight, innerBottomRight); //draw the upper line from topright to bottomright
    board.drawLine(innerBottomRight, innerBottomLeft); //draw the upper line from bottomright to bottomLeft
    board.drawLine(innerBottomLeft, innerTopLeft); //draw the upper line from bottomleft to topLeft
}

//------------------------------------------------------------------------------------------
//return the smallest blocking Rectangle
Rectangle Window::getBoundingRectangle() const
{
    Vertex outerBottomLeft = m_outer.getBottomLeft(), 
           outerTopRight = m_outer.getTopRight();
    Rectangle r1(outerBottomLeft, outerTopRight);
    return r1;
}

//------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//return the Rectangle's area
double Window::getArea() const
{
    //calculate area by Width * Height;
    return (m_outer.getWidth() * m_outer.getHeight()) - (m_inner.getWidth() * m_inner.getHeight());
}

//---------------------------------------------------------------------------------
//return the Rectangle's Perimeter
double Window::getPerimeter() const
{
    return (m_outer.getWidth() * 2 + m_outer.getHeight() * 2) + (m_inner.getWidth() * 2 + m_inner.getHeight() * 2);
}

//-----------------------------------------------------------------------------------
//set the new rentangles with scalling, and return true if it's done, else return false.
bool Window::scale(double factor)
{
    if (factor < 0)//negetive scale is not possible
        return false;
    //Instrumental variable to help us get the new points of the outer rectangle
    Vertex new_outerBottomLeft, new_outerTopRight, 
           Center = m_outer.getCenter();
    //Instrumental variable to help us get the new points of the inner rectangle
    Vertex new_innerBottomLeft, new_innerTopRight;

    new_outerBottomLeft.m_col = Center.m_col - ((m_outer.getWidth() * factor) / 2);
    new_outerBottomLeft.m_row = Center.m_row - ((m_outer.getWidth() * factor) / 2);
    new_outerTopRight.m_col = Center.m_col + ((m_outer.getHeight() * factor) / 2);
    new_outerTopRight.m_row = Center.m_row + ((m_outer.getHeight() * factor) / 2);


    new_innerBottomLeft.m_col = Center.m_col - ((m_inner.getWidth() * factor) / 2);
    new_innerBottomLeft.m_row = Center.m_row - ((m_inner.getWidth() * factor) / 2);
    new_innerTopRight.m_col = Center.m_col + ((m_inner.getHeight() * factor) / 2);
    new_innerTopRight.m_row = Center.m_row + ((m_inner.getHeight() * factor) / 2);
   
    if (!new_outerBottomLeft.isValid() || !new_outerTopRight.isValid()
        || !new_innerBottomLeft.isValid() || !new_innerTopRight.isValid())
        return false;
    
    m_outer.set(new_outerBottomLeft, new_outerTopRight);
    m_inner.set(new_innerBottomLeft, new_innerTopRight);

    return true;
}


//---------------------------------------------------------------------------------
//return rectangle's center
Vertex Window::getCenter() const
{
    Vertex center = m_outer.getCenter();
    return center;
}
    
//--------------------------------------------------------------------------------
//get the outside rectangle, and the inside rectangle.
//check if there is a valid window
bool Window::isvalidWindow(const Rectangle& outer, const Rectangle& inner)
{
 
    Vertex outerbottom, outertop, innerbottom, innertop, outercenter, innercenter;

    outerbottom = outer.getBottomLeft();
    outertop = outer.getTopRight();
    innerbottom = inner.getBottomLeft();
    innertop = inner.getTopRight();
    outercenter = outer.getCenter();
    innercenter = inner.getCenter();

    if (innertop.m_col > outertop.m_col || innertop.m_row > outertop.m_row
        || innerbottom.m_col < outerbottom.m_col || innerbottom.m_row < outerbottom.m_row
        || (outercenter.m_col - innercenter.m_col) > 0.1 || (outercenter.m_col - innercenter.m_col) < -0.1
        || (outercenter.m_row - innercenter.m_row) > 0.1 || (outercenter.m_row - innercenter.m_row) < -0.1)
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------
//get the outside rectangle, and the distance from the inside rectangle
//check if there is a valid window
bool Window::isvalidWindow(const Rectangle& outer, double verticalThickness, double horizontalThickness)
{
    double recHeight = outer.getHeight(),
           recLength = outer.getWidth();
    if (verticalThickness > (recHeight / 2) || 
        horizontalThickness > (recLength / 2))
        return false;
    return true;
}

//-------------------------------------------------------------------------------------------------
//if there was an error with the data, set the defult values.
void Window::defultset()
{
    m_inner.defultset();
    m_outer.defultset();
}
