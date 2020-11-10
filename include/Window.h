#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "Board.h"

class Window 
{
public:
    Window(const Rectangle& outer, const Rectangle& inner);
    Window(const Rectangle& outer, double verticalThickness, double horizontalThickness);
    Vertex getBottomLeft() const;
    Vertex getTopRight() const;
    Vertex getCenter() const;
    double getVerticalThickness() const;
    double getHorizontalThickness() const;
    void draw(Board& Board) const;
    Rectangle getBoundingRectangle() const;
    double getArea() const;
    double getPerimeter() const;
    bool scale(double factor);

private:
    Rectangle m_inner,
              m_outer;

    bool isvalidWindow(const Rectangle& outer, const Rectangle& inner);
    bool isvalidWindow(const Rectangle& outer, double verticalThickness, double horizontalThickness);
    void defultset();


};
