#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
using std::string;

struct Usuario {
    char id[20];
    char nombreCompleto[50];
    char carnet[15];
    char password[20];
};

class Usuarios {
private:
    string currentUser;
    string currentFullName;
    string currentCarnet;
    bool loggedIn;
public:
    Usuarios();
    bool login();
    void logout();
    string getNombreUsuario() const;
    string getNombreCompleto() const;
    string getCarnet() const;
    bool estaAutenticado() const;
    static void crearArchivoSiNoExiste();
};

#endif
