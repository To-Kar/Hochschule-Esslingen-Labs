#include <string>
using namespace std;

/* HIER */
#include "Employee.h"

class Manager : Employee/* HIER */
{
    double _salary;

public:
    Manager(const string, const string, double);
    double get_income() const;
    void print() const;
};