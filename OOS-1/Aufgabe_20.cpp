#include <string>
#include <iostream>

// Implementierung

using namespace std;

class AuthenticationResult
{
    bool _authenticated;
    string _username;

public:
    AuthenticationResult(bool _authenticated, string _username);
    bool isAuthenticated();
    string getUsername();
    void setAuthenticated(bool _authenticated);
    void setUsername(string _username);
};

AuthenticationResult::AuthenticationResult(bool authenticated, string username = "unauthenticated_user")
    : _authenticated(authenticated), _username(username) {}
bool AuthenticationResult::isAuthenticated()
{
    return _authenticated;
}
string AuthenticationResult::getUsername()
{
    return _username;
}
void AuthenticationResult::setAuthenticated(bool authenticated)
{
    this->_authenticated = authenticated;
}
void AuthenticationResult::setUsername(string username)
{
    this->_username = username;
}

class IAuthenticationMethod
{
public:
    virtual AuthenticationResult authenticate() = 0;
};

class Client
{
    IAuthenticationMethod *_authentication_method = nullptr;
    AuthenticationResult authResult = AuthenticationResult(false, "unauthenticated_user");

public:
    void set_authentication_method(IAuthenticationMethod *auth);
    void execute();
};

void Client::set_authentication_method(IAuthenticationMethod *auth)
{
    this->_authentication_method = auth;
}

void Client::execute()
{
    authResult = _authentication_method->authenticate();
    if (authResult.isAuthenticated())
    {
        cout << "Das Programm wird ausgeführt für " << authResult.getUsername() << "." << endl;
    }
    else
    {
        cout << "Das Programm konnte nicht ausgeführt werden." << endl;
    }
}

class MockAuthentication : public IAuthenticationMethod
{
public:
    AuthenticationResult authenticate();
};

AuthenticationResult MockAuthentication::authenticate()
{
    return AuthenticationResult(true, "Default");
}

class UsernamePassword : public IAuthenticationMethod
{
public:
    AuthenticationResult authenticate();
};

AuthenticationResult UsernamePassword::authenticate()
{
    string username;
    string password;
    cout << "Username: " << endl;
    cin >> username;
    cout << "Password: " << endl;
    cin >> password;
    if (username == password)
    {
        return AuthenticationResult(true, username);
    }
    else
    {
        return AuthenticationResult(false, username);
    }
}

class Certificate : public IAuthenticationMethod
{
public:
    AuthenticationResult authenticate();
};

AuthenticationResult Certificate::authenticate()
{
    string certOwner;
    cout << "Zertifikatsaussteller: " << endl;
    cin >> certOwner;
    if (certOwner == "hs-esslingen")
    {
        return AuthenticationResult(true, "certificate.owner");
    }
    else
    {
        return AuthenticationResult(false);
    }
}

int main(int argc, char *argv[])
{
    Client client;

    cout << "Authentifizierung über die Authentifizierungsmethode Mock Authentication" << endl;
    IAuthenticationMethod *mock_authentication = new MockAuthentication();
    client.set_authentication_method(mock_authentication);
    client.execute();

    cout << "Authentifizierung über die Authentifizierungsmethode Username Password" << endl;
    IAuthenticationMethod *username_password = new UsernamePassword();
    client.set_authentication_method(username_password);
    client.execute();

    cout << "Authentifizierung über die Authentifizierungsmethode Zertifikat" << endl;
    IAuthenticationMethod *certificate = new Certificate();
    client.set_authentication_method(certificate);
    client.execute();
    return 0;
}
