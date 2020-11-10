#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "vertex.h"
#include "Board.h"
#include "Rectangle.h"


class IsoscelesTriangle 
{
public:
    IsoscelesTriangle(const Vertex vertices[3]);
    IsoscelesTriangle(const Vertex& v0, const Vertex& v1, double height);
    Vertex getVertex(int index) const;
    double getBaseLength() const;
    double getLegLength() const;
    double getHeight() const;
    void draw(Board& board) const;
    Rectangle getBoundingRectangle() const;
    double getArea() const;
    double getPerimeter() const;
    Vertex getCenter() const;
    bool scale(double factor);
private:
    Vertex m_BottomLeft,
           m_BottomRight,
           m_Middle;
    bool isvalidIsoscelesTriangle(const Vertex& left, const Vertex& right, const Vertex& middle);
    void defultset();


};
