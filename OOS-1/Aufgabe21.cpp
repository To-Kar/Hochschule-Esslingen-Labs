#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

// Eigene Exceptionklasse "MyException"
// abgeleitet von Exception
class MyException : public exception {// HIER {
   public:
        string file;
        int line;
        string message;
        MyException(string file, int line, string msg);
        virtual const char* what() const noexcept override;
};

MyException::MyException(string file, int line, string msg)
: file(file), line(line), message(msg)
{
}

const char* MyException::what() const noexcept
{
    return message.c_str();
}

// Eigene Exceptionklasse "ElefantMeetsMouse"
// abgeleitet von MyException
class ElefantMeetsMouse : public MyException
{
    // HIER
    public:
        ElefantMeetsMouse(string file, int line, string msg);
};

ElefantMeetsMouse::ElefantMeetsMouse(string file, int line, string msg)
: MyException(file, line, msg)
{
}


// Klasse der Tiere
class Animal
{
    // Name des Tiers
    string _name;

public:
    // Konstruktor
    Animal(string n = "") : _name(n)
    {
        cout << "Bitte Namen des Tieres eingeben: ";
        cin >> _name;
    };
    
    // virtuelle print-Funktion
    virtual void print(bool nl) const
    {
        cout << _name;
        if (nl)
        {
            cout << endl;
        }
    }
    virtual Animal *clone() const = 0;
};

// Klasse "Elefant"
// abgeleitet von Animal
class Elefant : public Animal {
    // HIER
public:
    Elefant(string n = " ") : Animal(n) {}
virtual Elefant* clone() const {
    return new Elefant(*this);
}
};

// Klasse "Tiger"
// abgeleitet von Animal
class Tiger : public Animal {
    // HIER
public:
    Tiger(string n = " ") : Animal(n) {}
virtual Tiger* clone() const {
    return new Tiger(*this);
}
};

// Klasse "Mouse"
// abgeleitet von Animal
class Mouse : public Animal {
    // HIER
public:
    Mouse(string n = " ") : Animal(n) {}
    virtual Mouse* clone() const {
    return new Mouse(*this);
}
};

class Zoo
{
    // Name des Zoos
    string _name;
    // Die Tiere werden in einem Vektor gespeichert
    vector<Animal *> animals;

public:
    // Konstruktor
    Zoo()
    {
        // Name zuweisen
        cout << "Bitte Name des Zoos eingeben: ";
        cin >> _name;
        // Wenn der String kuerzer als 4 Zeichen ist,
        // dann MyException werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        // HIER
        if(_name.length() < 4) {
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            throw MyException(__FILE__, __LINE__, "Fehler 'Zoo name zu kurz' ");
        }
        // Ansonsten, den 5. Buchstaben des Namens gross machen
        _name.at(4) = toupper(_name.at(4));
    }

    // Ein Tier dem Zoo hinzufuegen
    void add_animal(const Animal &animal)
    {
        // Wenn ein Elefant nach einer Maus eingefuegt wird, oder anders herum
        // dann Ausnahme werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        // HIER
        if(animals.size() > 0) {
            if ((typeid(*animals[animals.size()-1]) == typeid(Elefant) && typeid(animal) == typeid(Mouse))
                || (typeid(*animals[animals.size()-1]) == typeid(Mouse) && typeid(animal) == typeid(Elefant))){
                throw ElefantMeetsMouse(__FILE__, __LINE__, "Fehler 'Elefant trifft auf Maus' ");
            }
        }
        animals.push_back(animal.clone());
    }

        // sonst Tier hinzufuegenW
        // HIER
        
    // Alle Zootiere ausgeben
    void print() const
    {
        // HIER
        for(auto it = animals.begin(); it != animals.end(); it++) {
            (*it)->print(true);
        }
    }
};

int main(int argc, char *argv[])
{
    char choice;
    string name;

    // Ausnahmepruefung aktivieren
    // HIER
    
    try {
        Zoo zoo;
        do
        {
            cout << endl
            << "Bitte Tierart auswaehlen:" << endl;
            cout << "1 = Elefant" << endl;
            cout << "2 = Tiger" << endl;
            cout << "3 = Maus" << endl;
            cout << "e = Ende mit Eingabe" << endl;
            cout << "Eingabe: ";
            cin >> choice;
            switch (choice)
            {
                case '1':
                {
                    Elefant elefant = Elefant();
                    zoo.add_animal(elefant);
                    break;
                }
                case '2':
                {
                    Tiger tiger = Tiger();
                    zoo.add_animal(tiger);
                    break;
                }
                case '3':
                {
                    Mouse mouse = Mouse();
                    zoo.add_animal(mouse);
                    break;
                }
                case 'e':
                    break;
                default:
                    // Einen String als Ausnahme werfen
                    // HIER
                    throw string("Fehlerhafte Eingabe!");
                    
            }
            
            cout << endl;
            zoo.print();
        } while (choice != 'e');
    }
    
    // Ausnahmen auffangen
    // Speziellste Ausnahme auffangen und ausgeben
    catch(ElefantMeetsMouse &e)
    {
        cout << e.what() << "aufgetreten in Datei " << e.file << ", Zeile: " << e.line << "." << endl;
    }
    
    // MyException auffangen und ausgeben
    // HIER
    catch(MyException &e) {
        cout << e.what() << "aufgetreten in Datei " << e.file << ", Zeile: " << e.line << "." << endl;
    }
    

    // Alle anderen Standardausnahmen auffangen und ausgeben
    // HIER
    catch(exception &e) {
        cout << "Standardausnahme: " << e.what() << endl;
    }

    // Alle Strings auffangen und ausgeben
    // HIER
    catch(string &e) {
        cout << e << endl;
    }
    

    // Alle anderen Ausnahmen auffangen
    // HIER
    catch(...) {
        cout << "Exception" << endl;
    }
    
    
    return 0;
}
