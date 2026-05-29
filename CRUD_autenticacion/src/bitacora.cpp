#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <ctime>

using namespace std;

void Bitacora::registrar(const string& usuario, const string& accion, const string& codigoApp) {
    ofstream file("bitacora.dat", ios::binary | ios::app);
    if (!file) return;

    LogEntry entry;
    strcpy(entry.nombreUsuario, usuario.c_str());
    strcpy(entry.accion, accion.c_str());
    strcpy(entry.codigoAplicacion, codigoApp.c_str());

    time_t now = time(nullptr);
    char* dt = ctime(&now);
    dt[strlen(dt)-1] = '\0';
    strcpy(entry.fechaHora, dt);

    file.write(reinterpret_cast<char*>(&entry), sizeof(LogEntry));
    file.close();
}

void Bitacora::mostrarTodos() {
    system("cls");
    ifstream file("bitacora.dat", ios::binary);
    if (!file) {
        cout << "\nNo hay registros.\n";
        system("pause");
        return;
    }

    LogEntry entry;
    cout << "\n===== BITÁCORA DE SEGURIDAD =====\n";
    cout << left << setw(20) << "USUARIO" << setw(15) << "ACCIÓN" << setw(15) << "CÓDIGO" << setw(30) << "FECHA/HORA" << endl;
    while (file.read(reinterpret_cast<char*>(&entry), sizeof(LogEntry))) {
        cout << left << setw(20) << entry.nombreUsuario
             << setw(15) << entry.accion
             << setw(15) << entry.codigoAplicacion
             << setw(30) << entry.fechaHora << endl;
    }
    file.close();
    system("pause");
}
