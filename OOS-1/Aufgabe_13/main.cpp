#pragma once
#include <iostream>

#include "Worker.h"
#include "Manager.h"

using namespace std;

/* HIER */


int main()
{
    Manager m("Karaqi", "Tom", 1000.00);
    m.print();
    cout << "Gehalt: " << m.get_income() << endl << endl;
    Worker w("Peter", "Mueller", 15.00, 40);
    w.print();
    cout << "Lohn: " << w.get_income() << endl;
    return 0;
}