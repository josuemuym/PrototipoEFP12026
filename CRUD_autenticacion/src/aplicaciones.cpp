#include "aplicaciones.h"
#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>

using namespace std;

Bodega::Bodega(const string& usuario) : usuarioActual(usuario) {}

void Bodega::menu() {
    int choice;
    char x;
    do {
        system("cls");
        cout << "\t\t\t------------------------------------" << endl;
        cout << "\t\t\t| SISTEMA GESTION BODEGA - 800      |" << endl;
        cout << "\t\t\t------------------------------------" << endl;
        cout << "\t\t\t 1. Ingreso bodega" << endl;
        cout << "\t\t\t 2. Despliegue bodega" << endl;
        cout << "\t\t\t 3. Modifica bodega" << endl;
        cout << "\t\t\t 4. Busca bodega" << endl;
        cout << "\t\t\t 5. Borra bodega" << endl;
        cout << "\t\t\t 6. Regresar" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\tOpcion: ";
        cin >> choice;

        switch (choice) {
            case 1:
                do {
                    insertar();
                    cout << "\n\t\t\t Agregar otra bodega (Y/N): ";
                    cin >> x;
                } while (x == 'y' || x == 'Y');
                break;
            case 2:
                desplegar();
                break;
            case 3:
                modificar();
                break;
            case 4:
                buscar();
                break;
            case 5:
                borrar();
                break;
            case 6:
                break;
            default:
                cout << "\n\t\t\t Opcion invalida...";
                cin.get();
        }
    } while (choice != 6);
}

void Bodega::insertar() {
    system("cls");
    RegistroBodega reg;
    cout << "\n--- AGREGAR BODEGA ---\n";
    cout << "ID: "; cin >> reg.id;
    cout << "Nombre: "; cin >> reg.nombre;
    cout << "Estatus: "; cin >> reg.estatus;

    ofstream file("bodega.dat", ios::binary | ios::app);
    if (!file) {
        cout << "Error al abrir archivo.\n";
        system("pause");
        return;
    }
    file.write(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega));
    file.close();

    Bitacora::registrar(usuarioActual, "INS", "800");
    cout << "\nBodega agregada.\n";
    system("pause");
}

void Bodega::desplegar() {
    system("cls");
    ifstream file("bodega.dat", ios::binary);
    if (!file) {
        cout << "\nNo hay registros.\n";
        system("pause");
        return;
    }

    RegistroBodega reg;
    bool hay = false;
    cout << "\n--- LISTA DE BODEGAS ---\n";
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega))) {
        hay = true;
        cout << "ID: " << reg.id << "\tNombre: " << reg.nombre << "\tEstatus: " << reg.estatus << endl;
    }
    file.close();
    if (!hay) cout << "No hay bodegas.\n";
    Bitacora::registrar(usuarioActual, "SEL", "800");
    system("pause");
}

void Bodega::modificar() {
    system("cls");
    char idBuscado[15];
    cout << "ID de bodega a modificar: ";
    cin >> idBuscado;

    fstream file("bodega.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error al abrir archivo.\n";
        system("pause");
        return;
    }

    RegistroBodega reg;
    bool encontrado = false;
    long pos;
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega))) {
        if (strcmp(reg.id, idBuscado) == 0) {
            encontrado = true;
            pos = file.tellg() - sizeof(RegistroBodega);
            cout << "Nuevo nombre: "; cin >> reg.nombre;
            cout << "Nuevo estatus: "; cin >> reg.estatus;
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega));
            Bitacora::registrar(usuarioActual, "UPD", "800");
            cout << "Modificado.\n";
            break;
        }
    }
    file.close();
    if (!encontrado) cout << "ID no encontrado.\n";
    system("pause");
}

void Bodega::buscar() {
    system("cls");
    char idBuscado[15];
    cout << "ID a buscar: ";
    cin >> idBuscado;

    ifstream file("bodega.dat", ios::binary);
    if (!file) {
        cout << "No hay datos.\n";
        system("pause");
        return;
    }

    RegistroBodega reg;
    bool encontrado = false;
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega))) {
        if (strcmp(reg.id, idBuscado) == 0) {
            cout << "ID: " << reg.id << "\nNombre: " << reg.nombre << "\nEstatus: " << reg.estatus << endl;
            encontrado = true;
            break;
        }
    }
    file.close();
    if (!encontrado) cout << "No existe.\n";
    Bitacora::registrar(usuarioActual, "SEL", "800");
    system("pause");
}

void Bodega::borrar() {
    system("cls");
    char idBuscado[15];
    cout << "ID a eliminar: ";
    cin >> idBuscado;

    ifstream file("bodega.dat", ios::binary);
    ofstream temp("temp_bodega.dat", ios::binary);
    if (!file || !temp) {
        cout << "Error de archivo.\n";
        system("pause");
        return;
    }

    RegistroBodega reg;
    bool eliminado = false;
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega))) {
        if (strcmp(reg.id, idBuscado) == 0) {
            eliminado = true;
            continue;
        }
        temp.write(reinterpret_cast<char*>(&reg), sizeof(RegistroBodega));
    }
    file.close();
    temp.close();

    if (eliminado) {
        remove("bodega.dat");
        rename("temp_bodega.dat", "bodega.dat");
        Bitacora::registrar(usuarioActual, "DEL", "800");
        cout << "Eliminado.\n";
    } else {
        remove("temp_bodega.dat");
        cout << "ID no encontrado.\n";
    }
    system("pause");
}
