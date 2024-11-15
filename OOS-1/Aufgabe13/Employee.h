#pragma once

#include <string>
using namespace std;

class Employee
{
    string _first_name;
    string _last_name;
 
public:
    Employee(const string, const string);
    void print() const;
};