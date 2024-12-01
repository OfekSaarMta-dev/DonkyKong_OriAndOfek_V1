#pragma once

class Point 
{
public:
    int _x, _y;

    Point(int x, int y) : _x(x), _y(y) {}
    

    // Getters
    int getX() const { return _x; }
    int getY() const { return _y; }

    // Setters
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }

    // Utility functions
    void setXY(int x, int y) {
        _x = x;
        _y = y;
    }


    Point operator+(const Point& other) const 
    { 
        return Point(_x + other._x, _y + other._y);
    }

    Point& operator+=(const Point& other) 
    {
        _x += other._x; _y += other._y; return *this; 
    }
    bool operator==(const Point& other) const 
    { 
        return _x == other._x && _y == other._y; 
    }

    Point& operator=(const Point& other) {
        if (this != &other) {
            _x = other._x;
            _y = other._y;
        }
        return *this;
    }

    // FOR EXAMPLE P1 = P2 + P3
};