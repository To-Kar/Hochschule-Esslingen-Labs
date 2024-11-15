//
//  main.cpp
//  OOS 19
//
//  Created by Tom on 18.05.23.
////
//#include <iostream>
//#include <vector>
//#include <string>
//#include <array>
//
//using namespace std;
//Schreiben Sie die abstrakte Basisklasse 'Meal' mit den Methoden 'add_topping' und 'prepare'. Implementieren sie die Klassen Pizza und Burger, sodass das vorhandene Programmfragment kompiliert werden und mittels der Zeile *[1] folgendes auf der Konsole ausgegeben werden kann:
//
//Pizza Mista. Pizzaboden, belegt mit:
//- Salami
//- Pilzen
//Pizza Hawaii. Pizzaboden, belegt mit:
//- Schinken
//- Ananas
//Hamburger. Brötchen mit:
//- Hackfleisch
//Cheesburger. Brötchen mit:
//- Hackfleisch
//- Käse
//Nutzen Sie die Vererbung von Instanzvariablen und Instanzmethoden entsprechend.

//class Meal
//{
//private:
//public:
//    virtual void add_topping(string) = 0;
//    virtual void prepare() = 0;
//};
//
//class Pizza : public Meal
//{
//private:
//    string name;
//    vector<string> toppings;
//public:
//    void add_topping(string) override;
//    void prepare() override;
//};
//
//int main(int argc, char* argv[])
//{
//    Pizza *mista = new Pizza("Mista");
//    mista->add_topping("Salami");
//    mista->add_topping("Pilzen");
//    Meal *hawaii = new Pizza("Hawaii");
//    hawaii->add_topping("Schinken");
//    hawaii->add_topping("Ananas");
//    Burger *hamburger = new Burger("Hamburger");
//    hamburger->add_topping("Hackfleisch");
//    Meal *cheesburger = new Burger("Cheesburger");
//    cheesburger->add_topping("Hackfleisch");
//    cheesburger->add_topping("Käse");
//    array<Meal *, 4> menu = {mista, hawaii, hamburger, cheesburger};
//    for (Meal *g : menu)
//    {
//        g->prepare(); //*[1]
//    }
//    return 0;
//}
#include <string>
#include <iostream>
using namespace std;

class Person {
    string _name;
    int _check_out_duration;
public:

    Person(string name, int check_out_duration = 0);
    int get_check_out_duration() const;
    void print() const;


};

// Implmentierung des Konstruktors und der Methoden
Person::Person(string name, int check_out_duration) : _name(name), _check_out_duration(check_out_duration) {}

int Person::get_check_out_duration() const
{
    return _check_out_duration;
}

void Person::print() const
{
    cout << _name;
}

class Lecturer : public Person
{
    int _examiner_id;
    
public:
    Lecturer(string name, int examiner_id);
    void print() const;
};

Lecturer::Lecturer(string name, int examiner_id) : Person(name, 90), _examiner_id(examiner_id) {}
void Lecturer::print() const
{
    cout << ", Prüfernummer " << _examiner_id << endl;
}
// Implmentierung des Konstruktors und der Methoden

class Student : public Person
{
    int _matriculation_number;
    string name;
    

public:

    Student(string name, int matriculation_number);
    void print() const;
};

Student::Student(string name, int matriculation_number) : Person(name, 30), _matriculation_number(matriculation_number) {}


void Student::print() const
{
    cout << ", Matrikelnummer " << _matriculation_number << endl;
}
// Implmentierung des Konstruktors und der Methoden

int main(int argc, char* argv[]) {
    Student smith = Student("smith", 12345678);
    Lecturer miller = Lecturer("miller", 98);
    smith.print();
    cout << "Ausleihdauer: " << smith.get_check_out_duration() << " Tage(e)" << endl;
    miller.print();
    cout << "Ausleihdauer: " << miller.get_check_out_duration() << " Tage(e)" << endl;
}

