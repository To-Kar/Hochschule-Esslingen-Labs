

#include <iostream>
using namespace std;

class Point
{
private:
    double _x; // x-Koordinate
    double _y; // y-Koordinate
public:
    Point(double x = 0, double y = 0) : _x(x), _y(y) {}

    void set_x(double _x)
    {
        this->_x = _x;
    }

    void set_y(double _y)
    {
        this->_y = _y;
    }

    double get_x()
    {
        return this->_x;
    }

    double get_y()
    {
        return this->_y;
    }

    void move(double dx, double dy)
    {
        set_x(get_x() + dx);
        set_y(get_y() + dy);
    }

    void print(bool b = true)
    {
        cout << "(" << get_x() << ", " << get_y() << ")";
        if (b == true)
        {
            cout << endl;
        }
    }
};

class Circle
{
private:
    Point _centre;
    double _radius;

public:
    Circle(Point centre, double radius = 1) : _centre(centre), _radius(radius) {}

    void set_centre(Point p)
    {
        this->_centre = p;
    }

    void set_radius(double radius)
    {
        this->_radius = radius;
    }

    void move(double dx, double dy)
    {
        _centre.set_x(_centre.get_x() + dx);
        _centre.set_y(_centre.get_y() + dy);
    }

    void print()
    {
        cout << "[(" << _centre.get_x() << ", " << _centre.get_y() << "), " << _radius << "]" << endl;
    }
};

int main(int argc, char *argv[])
{
    Point p;
    Circle c(p);
    cout << "Ausgabe 1:" << endl;
    p.print();
    c.print();
    p.set_x(1.1);
    p.set_y(2.2);
    c.set_centre(p);
    c.set_radius(3.3);
    cout << "Ausgabe 2:" << endl;
    p.print(false);
    cout << " == (" << p.get_x() << ", " << p.get_y() << ")"
         << endl;
    c.print();
    p.move(1.0, 1.0);
    c.move(2.0, 2.0);
    cout << "Ausgabe 3:" << endl;
    p.print();
    c.print();
    return 0;
}
