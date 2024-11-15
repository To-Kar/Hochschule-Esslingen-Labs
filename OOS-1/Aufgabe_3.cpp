#include <iostream>
using namespace std;

class Point
{

    int x;
    int y;

public:
    void set_x(int i)
    {
        x = i;
    }
    void set_y(int i)
    {
        y = i;
    }
    int get_x()
    {

        return x;
    }
    int get_y()
    {
        return y;
    }
    void print()
    {
        cout << "print-Methode:" << endl
             << "X = " << x << endl
             << "Y = " << y << endl;
    }
};

int main(int argc, char *argv[])
{
    Point p;
    p.set_x(1);
    p.set_y(10);
    p.print();
    p.set_x(5);
    cout << "X ohne print(): " << p.get_x() << endl;
    cout << "Y ohne print(): " << p.get_y() << endl;
    return 0;
}