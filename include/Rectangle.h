#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "vertex.h"
#include "Board.h"


class Rectangle
{
public:
    Rectangle() = default;
    Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
    Rectangle(const Vertex vertices[2]);
    Rectangle(double x0, double y0, double x1, double y1);
    Rectangle(const Vertex& center, double width, double height);
    Vertex getBottomLeft() const;
    Vertex getTopRight() const;
    Vertex getCenter() const;
    void draw(Board& board) const;
    double getHeight() const;
    double getWidth() const;
    bool scale(double factor);
    Rectangle getBoundingRectangle() const;   
    double getArea() const;
    double getPerimeter() const;
    void set(const Vertex& bottomLeft, const Vertex& topRight);
    void defultset();

private:
    Vertex m_BottomLeft,
           m_TopRight;
    bool checkRctangleCond(Vertex bottomLeft, Vertex topRight);
    bool isDataValid(double width, double height);
};
