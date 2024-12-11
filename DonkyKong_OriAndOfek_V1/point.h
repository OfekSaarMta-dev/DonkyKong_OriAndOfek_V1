#pragma once

class Point 
{
    int _x, _y;


public:

    Point() : _x(0), _y(0) {}
    Point(int x, int y) : _x(x), _y(y) {}
    

    // Getters
    int getX() const { return _x; }
    int getY() const { return _y; }

    // Setters
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }


};