#include <iostream>
#include <string>
using namespace std;

class A
{
public:
    void method_1()
    {
        cout << "A::method_1()" << endl;
    }
    void method_2(double d)
    {
        cout << "A::method_2(double)" << endl;
    }
    void method_2(string s)
    {
        cout << "A::method_2(string)" << endl;
    }
    void method_3(char c)
    {
        cout << "A::method_3(char)" << endl;
    }
    void method_3(string s)
    {
        cout << "A::method_3(string)" << endl;
    }
};

class B : public A
{
public:
    void method_2(int i)
    {
        cout << "B::method_2(int)" << endl;
    }
    void method_3(int i)
    {
        cout << "B::method_3(int)" << endl;
    }
    void method_3(string s)
    {
        cout << "B::method_3(string)" << endl;
    }
};

int main(int argc, char *argv[])
{
    A a;
    B b;
    cout << "a.method_1() ";
    a.method_1(); // a) keine Fehlermeldung;	b) Ausgabe: a.method_1(): A::method_1()
    cout << "b.method_1() ";
    b.method_1(); // a) keine Fehlermeldung;  b) Ausgabe: b.method_1(): A::method_1()
    cout << "a.method_2(1.2) ";
    a.method_2(1.2); // a) keine Fehlermeldung; b) Ausgabe: a.method_2(1.2): A::method_2(double)
    cout << "b.method_2(1.2) ";
    b.method_2(1.2); // a) keine Fehlermeldung; b) Ausgabe: b.method_2(1.2): B::method_2(int)
    cout << "a.method_2(1) ";
    a.method_2(1); // a) keine Fehlermeldung; b) Ausgabe: a.method_2(1): A::method_2(double)
    cout << "b.method_2(1) ";
    b.method_2(1); // a) keine Fehlermeldung; b) Ausgabe: b.methdod_2(1) B::method_2(int)
    cout << "a.method_2('c') ";
    a.method_2('c'); // a) keine Fehlermeldung; b) Ausgabe: a.method_2('c') A::method_2(double)
    cout << "b.method_2('c') ";
    b.method_2('c'); // a) keine Fehlermeldung; b) Ausgabe: b.method_2('c') B::method_2(int)
    cout << "a.method_2(''string'') ";
    a.method_2("string"); // a) keine Fehlermeldung; b) Ausgabe: a.method_2(''string'') A::mehtod_2(string)
    // cout << "b.method_2(''string'') ";
    // b.method_2("string");
    cout << "a.method_3(1) ";
    a.method_3(1); // a) keine Fehlermeldung b) b.method_2(1) A::method_3(char)
    cout << "b.method_3(1) ";
    b.method_3(1); // a) keine Fehlermeldung b) b.method_3(1) B::method_3(int)
    cout << "a.method_3('c') ";
    a.method_3('c'); // a) keine Fehlermeldung b) a.methdo_3('c') A::method_3(char)
    cout << "b.method_3('c') ";
    b.method_3('c'); // a) keine Fehlermeldung b) b.method_3('c') B::method_3(int)
    cout << "a.method_3(''string'') ";
    a.method_3("string"); // a) keine Fehlermeldung b) a.method_3(''string'') A::method_3(string)
    cout << "b.method_3(''string'') ";
    b.method_3("string"); // a) keine Fehlermeldung b) b.method_3(''string'') B::method_3(string)
    return 0;
}

// Aufgabe c)
// Funktion      | überlädt, verdeckt oder redefiniert.| Funktion
//-------------------------------------------------------------------
// void B::method_2(int) | verdeckt						| void A::method_2(double)
// void B::method_3(int) | überlädt						| void B::method_3(string)
// void B::method_3(string) | redefiniert + verdeckt		| void A::method_3(string

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg:
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
