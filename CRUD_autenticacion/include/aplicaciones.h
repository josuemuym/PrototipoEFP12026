#ifndef APLICACIONES_H
#define APLICACIONES_H

#include <string>
using std::string;

struct RegistroBodega {
    char id[15];
    char nombre[30];
    char estatus[15];
};

class Bodega {
private:
    string usuarioActual;  // para registrar en bitácora
public:
    Bodega(const string& usuario);  // constructor recibe el usuario logueado
    void menu();
    void insertar();
    void desplegar();
    void modificar();
    void buscar();
    void borrar();
};

#endif
