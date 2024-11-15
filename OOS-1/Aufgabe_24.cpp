#include <iostream>
#include <list>
#include <string>
#include <map>
#include <exception>

using namespace std;

class ISubscriber;

class Customer : public ISubscriber {
public:
    void update(const string& message) override {
        cout << "Customer " << _id << ": neue Nachricht verfügbar --> " << message << endl;
    }

    void setID(int id) {
        _id = id;
    }

private:
    int _id;
};

class GoldCustomer : public ISubscriber {
public:
    void update(const string& message) override {
        cout << "GoldCustomer " << _id << ": neue Nachricht verfügbar --> " << message << endl;
    }

    void setID(int id) {
        _id = id;
    }

private:
    int _id;
};

class ISubscriber {
public:
    virtual void update(const string& message) = 0;
    virtual ~ISubscriber() {}
};

class Store;

class Store {
public:
    Store() {
        _product_availability["iPhone"] = 0;
        _product_availability["Galaxy"] = 5;
    }

    void subscribe(ISubscriber* subscriber) {
        _subscribers.push_back(subscriber);
    }

    void unsubscribe(ISubscriber* subscriber) {
        _subscribers.remove(subscriber);
    }

    void notify_subscribers(const string& message) {
        for (ISubscriber* subscriber : _subscribers) {
            subscriber->update(message);
        }
    }

    void deliver_products(const string& product_type, unsigned int quantity) {
        unsigned int& availability = _product_availability[product_type];
        unsigned int initial_quantity = availability;
        availability += quantity;

        cout << "Vorrätige Artikel vom Typ " << product_type << ": " << initial_quantity << endl;
        cout << "Ausgelieferte Artikel vom Typ " << product_type << ": " << quantity << endl;
        cout << "Neuer Bestand: " << availability << endl;

        if (initial_quantity == 0) {
            string message = "Neue Artikel vom Typ " + product_type + " verfügbar.";
            notify_subscribers(message);
        }
    }

    void sell_products(const string& product_type, unsigned int quantity) {
        unsigned int& availability = _product_availability[product_type];

        if (quantity > availability) {
            string message = "Artikel vom Typ " + product_type + " nicht mehr verfügbar";
            notify_subscribers(message);
            throw out_of_range("Es sind nicht genügend Artikel vom Typ " + product_type + " verfügbar.");
        }

        unsigned int initial_quantity = availability;
        availability -= quantity;

        cout << "Vorrätige Artikel vom Typ " << product_type << ": " << initial_quantity << endl;
        cout << "Verkaufte Artikel vom Typ " << product_type << ": " << quantity << endl;
        cout << "Neuer Bestand: " << availability << endl;
    }

private:
    list<ISubscriber*> _subscribers;
    map<string, unsigned int> _product_availability;
};

void manage_store()
{
    try
    {
        Store *store = new Store;
        ISubscriber *customer_1 = new Customer();
        store->subscribe(customer_1);
        ISubscriber *customer_2 = new GoldCustomer();
        store->subscribe(customer_2);
        ISubscriber *customer_3 = new GoldCustomer();
        store->subscribe(customer_3);
        store->deliver_products("iPhone", 5);
        store->unsubscribe(customer_3);
        store->sell_products("iPhone", 3);
        ISubscriber *customer_4 = new Customer();
        store->subscribe(customer_4);
        store->deliver_products("iPhone", 5);
        store->sell_products("iPhone", 7);
        store->unsubscribe(customer_1);
        ISubscriber *customer_5 = new GoldCustomer();
        store->subscribe(customer_5);
        store->deliver_products("iPhone", 15);
        store->sell_products("Galaxy", 8);
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Ein unbekannter Fehler ist aufgetreten." << endl;
    }
}

int main(int argc, char *argv[])
{
    manage_store();
    return 0;
}
