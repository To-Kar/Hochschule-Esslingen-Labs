#include <iostream>
using namespace std;

/* HIER */
#include "Worker.h"

Worker::Worker(const string f_n, const string l_n,
                   double h_e, double h)
    : Employee(f_n, l_n), _hourly_earnings(h_e), _hours(h)
{
    /* HIER */

}
double Worker::get_income() const
{
    double salary = _hourly_earnings * _hours;
    return salary;
}

void Worker::print() const
{
    cout << "Worker: ";
    Employee::print();
}