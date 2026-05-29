#ifndef BITACORA_H
#define BITACORA_H

#include <string>
using std::string;

struct LogEntry {
    char nombreUsuario[30];
    char accion[10];
    char codigoAplicacion[10];
    char fechaHora[30];
};

class Bitacora {
public:
    static void registrar(const string& usuario, const string& accion, const string& codigoApp);
    static void mostrarTodos();
};

#endif
