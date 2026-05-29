#include "usuarios.h"
#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>

using namespace std;

Usuarios::Usuarios() : loggedIn(false) {}

void Usuarios::crearArchivoSiNoExiste() {
    ifstream file("usuarios.dat", ios::binary);
    if (!file) {
        ofstream out("usuarios.dat", ios::binary | ios::app);
        Usuario admin;
        strcpy(admin.id, "admin");
        strcpy(admin.nombreCompleto, "TU NOMBRE COMPLETO");  // CAMBIA AQUÍ
        strcpy(admin.carnet, "TU CARNET");                  // CAMBIA AQUÍ
        strcpy(admin.password, "admin123");
        out.write(reinterpret_cast<char*>(&admin), sizeof(Usuario));
        out.close();
        cout << "[SISTEMA] Usuario administrador creado.\n";
    }
    file.close();
}

bool Usuarios::login() {
    string user, pass;
    int intentos = 0;
    bool exito = false;

    do {
        system("cls");
        cout << "===============================\n";
        cout << "     AUTENTICACIÓN DE USUARIO   \n";
        cout << "===============================\n";
        cout << "Usuario: ";
        getline(cin, user);
        cout << "Contraseña: ";

        pass = "";
        char ch;
        while ((ch = getch()) != 13) {
            if (ch == 8) {
                if (!pass.empty()) {
                    cout << "\b \b";
                    pass.pop_back();
                }
            } else {
                pass.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        ifstream file("usuarios.dat", ios::binary);
        if (!file) {
            cout << "\nError de archivo.\n";
            cin.get();
            return false;
        }

        Usuario u;
        bool encontrado = false;
        while (file.read(reinterpret_cast<char*>(&u), sizeof(Usuario))) {
            if (user == u.id && pass == u.password) {
                encontrado = true;
                currentUser = u.id;
                currentFullName = u.nombreCompleto;
                currentCarnet = u.carnet;
                break;
            }
        }
        file.close();

        if (encontrado) {
            exito = true;
            loggedIn = true;
            cout << "\n=== ¡Bienvenido, " << currentFullName << "! ===\n";
            Bitacora::registrar(currentUser, "LOGS", "100");
            cin.get();
        } else {
            intentos++;
            cout << "\nUsuario o contraseña incorrectos. Intento " << intentos << " de 3.\n";
            Bitacora::registrar(user, "LOGF", "100");
            cin.get();
        }
    } while (!exito && intentos < 3);

    if (!exito) {
        cout << "\nAcceso denegado.\n";
        cin.get();
    }
    return exito;
}

void Usuarios::logout() {
    loggedIn = false;
    currentUser.clear();
    currentFullName.clear();
    currentCarnet.clear();
}

string Usuarios::getNombreUsuario() const { return currentUser; }
string Usuarios::getNombreCompleto() const { return currentFullName; }
string Usuarios::getCarnet() const { return currentCarnet; }
bool Usuarios::estaAutenticado() const { return loggedIn; }
