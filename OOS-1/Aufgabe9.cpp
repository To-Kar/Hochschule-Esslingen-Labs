//
//  main.cpp
//  OOS Aufgabe 9
//
//  Created by Tom on 29.10.23.
//

#include <iostream>
using namespace std;

class Date {
    
    int day, month, year;
    
public:
    Date(int = 0, int = 0, int = 0);
    Date operator+(int days);
    friend ostream& operator<<(ostream &, const Date &);
};


Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

Date Date::operator+(int days) {
    Date temp;
    
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    temp.day = day + days;
    temp.month = month;
    temp.year = year;
    while(temp.day > daysInMonth[temp.month - 1]) {
        temp.day -= daysInMonth[temp.month - 1];
        temp.month++;
        if (temp.month > 12) {
            temp.month = 1;
            temp.year++;
        }
    }
    return temp;
}

ostream & operator << (ostream & os, const Date & d) {
    os << d.day << "." << d.month << "." << d.year;
    return os;
}

int main(int argc, char * argv[]) {
    Date begin_task = Date(26, 10, 2023);
    cout << "Die Aufgabe beginnt am " << begin_task << endl;
    Date end_task = begin_task + 7;
    cout << "Die Aufgabe endet am " << end_task << endl;
    Date one_year_and_one_month_later = begin_task + 396;
    cout << "Ein Jahr und ein Monat nach dem Aufgabenbeginn ist der " << one_year_and_one_month_later << endl;
    Date threeYearsAndElevenMonthsLater = begin_task + 1430;
    cout << "Drei Jahre und 11 Monate nach dem Aufgabenbeginn ist der " << threeYearsAndElevenMonthsLater << endl;
}

//#include<iostream>
//using namespace std;
//
//class Datum {
//    
//    int tag, monat, jahr;
//
//public:
//    Datum(int = 0, int = 0, int = 0);
//    Datum operator+(int tage);
//    friend ostream & operator<<(ostream &, const Datum &);
//};
//
//// Implementierung des Konstruktors und der Operatoren
//
//Datum::Datum(int t, int m, int j) {
//    tag = t;
//    monat = m;
//    jahr = j;
//}
//
//Datum Datum::operator+(int tage) {
//    Datum temp;
//    // Addiere die Tage und berechne neues Datum
//    int tageImMonat[] = {31,28,31,30,31,30,31,31,30,31,30,31};
//    temp.tag = tag + tage;
//    temp.monat = monat;
//    temp.jahr = jahr;
//    while (temp.tag > tageImMonat[temp.monat-1]) {
//        temp.tag -= tageImMonat[temp.monat-1];
//        temp.monat++;
//        if (temp.monat > 12) {
//            temp.monat = 1;
//            temp.jahr++;
//        }
//    }
//    return temp;
//}
//
//ostream & operator<<(ostream & os, const Datum & d) {
//    os << d.tag << "." << d.monat << "." << d.jahr;
//    return os;
//}
//
//int main(int argc, char *argv[])
//{
//    Datum beginnAufgabe = Datum(26,10,2023); // Datum muss hier geändert werden
//    cout << "Die Aufgabe beginnt am " << beginnAufgabe << endl;
//    Datum endeAufgabe = beginnAufgabe + 6; // Tage müssen angepasst werden
//    cout << "Die Aufgabe endet am " << endeAufgabe << endl;
//    Datum einJahrMonatSpaeter = beginnAufgabe + 390; // Tage müssen angepasst werden
//    cout << "Ein Jahr und ein Monat nach Aufgabenbeginn ist der " << einJahrMonatSpaeter << endl;
//}
