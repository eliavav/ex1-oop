#pragma once

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "vertex.h"
#include "Board.h"
#include "Rectangle.h"


class EquilateralTriangle
{
public:
    EquilateralTriangle(const Vertex vertices[3]);
    double getLength() const;
    void draw(Board& board) const;
    Vertex getVertex(int index) const;
    Rectangle getBoundingRectangle() const;
    double getArea() const;
    double getPerimeter() const;
    Vertex getCenter() const;
    bool scale(double factor);

private:
    Vertex m_BottomLeft,
           m_BottomRight,
           m_Middle;
    bool isvalidEquilateralTriangle(const Vertex& left, const Vertex& right, const Vertex& middle);
    void defultset();


};
