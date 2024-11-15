#include <string>
#include "Employee.h"
using namespace std;

/* HIER */

class Worker : Employee /* HIER */
{
    double _hourly_earnings;
    double _hours;

public:
    Worker(const string, const string, double = 0.0, double = 0.0);
    double get_income() const;
    void print() const;
};